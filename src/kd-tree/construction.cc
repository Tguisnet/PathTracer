#include <raytracer/kd-tree/construction.hh>

#include <iterator>
#include <functional>
#include <stdexcept>
#include <vector>

#include <raytracer/kd-tree/kd-tree.hh>
#include <raytracer/types/triangle.hh>
#include <raytracer/constants.hh>

using namespace raytracer;

namespace extrema_types
{
    struct min
    {
        template <typename ForwardIt>
        static constexpr ForwardIt extrema(ForwardIt begin, ForwardIt end)
        {
            return std::min_element(begin, end);
        }
    };

    struct max
    {
        template <typename ForwardIt>
        static constexpr ForwardIt extrema(ForwardIt begin, ForwardIt end)
        {
            return std::max_element(begin, end);
        }
    };
}

template <typename ExtremaType>
static auto ith_extrema(const Triangle& triangle, unsigned i)
{
    auto ith_elem = [i](const auto& v) {
        return v[i];
    };

    std::array<float, 3> values;

    std::transform(triangle.vertices.begin(), triangle.vertices.end(), values.begin(),
                   ith_elem);

    return *ExtremaType::extrema(values.begin(), values.end());
}

/*
 * Returns extrema value for triangle vertices i-th coordinate
 */
template <typename ExtremaType>
static auto ith_extrema(const std::vector<const Triangle*>& triangles, unsigned i)
{
#ifndef NDEBUG
    if (triangles.empty())
        throw std::out_of_range("Cannot compute extrema of an empty triangle set");
#endif

    auto ith_extrema_acc = [i](const auto& a, const auto& b) {
        std::array<float, 2> values{a, ith_extrema<ExtremaType>(*b, i)};

        return *ExtremaType::extrema(values.begin(), values.end());
    };

    return std::accumulate(triangles.begin(), triangles.end(),
                           triangles[0]->vertices[0][i],
                           ith_extrema_acc);
}

static auto compute_aabb(const std::vector<const Triangle*>& triangles)
{
    if (triangles.empty())
        return AABB{Vector::Zero(), Vector::Zero()};

    AABB aabb;

    // Compute bounding box using vertices extremas
    for (unsigned i = 0; i < 3; ++i)
    {
        aabb.v_min[i] = ith_extrema<extrema_types::min>(triangles, i) - epsilon;
        aabb.v_max[i] = ith_extrema<extrema_types::max>(triangles, i) + epsilon;
    }

    return aabb;
}

using Node = KDTree::KDNode;

static auto create_leaf(std::vector<const Triangle*>& triangles)
{
    auto node = std::make_shared<Node>();

    node->aabb = compute_aabb(triangles);
    node->triangles = std::move(triangles);

    return node;
}

static constexpr float percent_to_rate(float percent)
{
    return percent / 100.;
}

#define COMPARE_TRIANGLES(Axis) \
[](const Triangle* a, const Triangle* b) \
{ \
    return a->barycenter()[Axis] < b->barycenter()[Axis]; \
}

std::shared_ptr<KDTree::KDNode> raytracer::build_kdtree(std::vector<const Triangle*> triangles, std::size_t depth)
{
    // Minimum triangles for splitting using KDTree
    static constexpr std::size_t min_triangles = 16;

    // Max percentage of triangles in both splits
    static constexpr float max_matches_rate = percent_to_rate(50.);

    // Min AABB size
    static constexpr float min_aabb_diagonal = 0.02f;

    // Max depth
    static constexpr std::size_t max_depth = 8192;

    // Comparison functions (with axis x, y or z)
    static const std::vector<
            std::function<bool(const Triangle*, const Triangle*)>
    > compare_functions{
            COMPARE_TRIANGLES(0),
            COMPARE_TRIANGLES(1),
            COMPARE_TRIANGLES(2)
    };

    // Check max depth and minimum triangles threshold
    if (depth >= max_depth || triangles.size() < min_triangles)
        return create_leaf(triangles);

    // Tries to find an axis matching rate conditions, starting with depth % 3
    auto axis = depth % 3;
    for (unsigned i = 0; i < 3; ++i)
    {
        std::nth_element(triangles.begin(),
                         triangles.begin() + triangles.size() / 2,
                         triangles.end(),
                         compare_functions[axis]);

        const auto& median_triangle = *triangles[triangles.size() / 2];
        auto median_value = median_triangle.barycenter()[axis];

        std::vector<const Triangle*> left_triangles, right_triangles;
        std::size_t matches = 0;

        for (auto triangle: triangles)
        {
            unsigned match = 0;

            if (ith_extrema<extrema_types::max>(*triangle, axis) - epsilon < median_value)
                left_triangles.push_back(triangle);
            else
                ++match;

            if (ith_extrema<extrema_types::min>(*triangle, axis) + epsilon > median_value)
                right_triangles.push_back(triangle);
            else
                ++match;

            if (!match)
                ++matches;

            // If between both, go by default to left
            else if (match == 2)
                left_triangles.push_back(triangle);
        }

        // No split, continue
        if (left_triangles.empty() || right_triangles.empty())
            continue;

        auto max_matches = static_cast<std::size_t>(max_matches_rate * triangles.size());
        if (matches > max_matches)
        {
            // Too many matches, will try with another angle
            axis = (axis + 1) % 3;
            continue;
        }

        auto node = std::make_shared<Node>();

        // Compute bounding box
        node->aabb = compute_aabb(triangles);

        if (node->aabb.diagonal() < min_aabb_diagonal)
        {
            node->triangles = std::move(triangles);
            return node;
        }

        // No need to keep triangles anymore: memory saved during recursion
        triangles.clear();

        // Recursively build the tree
#ifdef _OPENMP
# pragma omp parallel sections
#endif
        {
#ifdef _OPENMP
# pragma omp section
#endif
            {
                node->left = build_kdtree(std::move(left_triangles), depth + 1);
            }
#ifdef _OPENMP
# pragma omp section
#endif
            {
                node->right = build_kdtree(std::move(right_triangles), depth + 1);
            }
        }

        return node;
    }

    // No axis matched mutual triangles maximum rate, returns a leaf
    return create_leaf(triangles);
}
