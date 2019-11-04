#include <raytracer/kd-tree/kd-tree.hh>

#include <iterator>
#include <functional>
#include <stdexcept>
#include <vector>
#include <utility>

#include <raytracer/kd-tree/construction.hh>
#include <raytracer/kd-tree/traversal.hh>
#include <raytracer/types/triangle.hh>
#include <raytracer/types/vector.hh>

using namespace raytracer;

KDTree::KDTree(std::vector<Triangle>&& triangles)
        : triangles_(std::move(triangles))
{
    if (triangles_.empty())
        throw std::invalid_argument("No triangles for KDTree construction");

    std::vector<const Triangle*> triangle_ptrs;

    // Fill the triangle pointers vector
    std::transform(triangles_.begin(), triangles_.end(),
                   std::back_inserter(triangle_ptrs),
                   [](const auto& triangle) {
                       return &triangle;
                   });

    root_ = build_kdtree(triangle_ptrs);
}

KDTree::TriangleSet KDTree::intersect(const Vector& ray_origin, const Vector& ray) const
{
    // Large set to handle all triangles: no reallocation needed
    KDTree::TriangleSet triangle_set(triangles_.size());

    find_triangles(*root_, ray_origin, ray, triangle_set);

    return triangle_set;
}
