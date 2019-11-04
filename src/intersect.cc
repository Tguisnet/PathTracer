#include <raytracer/intersect.hh>

#include <raytracer/constants.hh>
#include <raytracer/kd-tree/kd-tree.hh>
#include <raytracer/types/scene.hh>
#include <raytracer/types/triangle.hh>
#include <raytracer/types/vector.hh>

using namespace raytracer;

static bool compute_intersect_triangle(const Vector& ray_o, const Vector& ray, const Triangle& triangle,
                                           Vector& intersection)
{
    const auto& vertices = triangle.vertices;

    /* two edges with vertex1 in common */
    Vector edge1 = vertices[1] - vertices[0];
    Vector edge2 = vertices[2] - vertices[0];

    /* cros product then a dot product to avoid a triple dot product */
    Vector h = ray.cross(edge2);
    float a = edge1.dot(h);

    /* if a is near 0, it means that h and edge1 are orthogonal
     * so it implies that the ray lies in the triangle's plane */
    if (std::abs(a) < epsilon)
        return false;

    float f = 1.f / a;
    Vector s = ray_o - vertices[0];
    float u = f * (s.dot(h));

    if (u < 0.0 || u > 1.0)
        return false;

    Vector q = s.cross(edge1);
    float v = f * ray.dot(q);

    if (v < 0.0 || u + v > 1.0)
        return false;

    float t = f * edge2.dot(q);

    /* we check t and not abs(t) because we don't want to check triangle behind the ray */
    if (t > epsilon)
    {
        intersection = ray_o + ray * t;
        return true;
    }

    /* line intersection, not ray intersection */

    return false;
}

const Triangle* raytracer::nearest_triangle(
        const Vector& origin,
        const KDTree& kd_tree,
        const Vector& ray,
        Vector& nearest_point
)
{
    auto min_dist = FLT_MAX;
    const Triangle* nearest_triangle_ptr = nullptr;

    for (const auto& triangle: kd_tree.intersect(origin, ray))
    {
        Vector intersection;

        /* Here we check if there is an intersection */
        bool intersect = compute_intersect_triangle(
                origin,
                ray,
                *triangle,
                intersection
        );

        if (!intersect)
            continue;

        auto dist = (intersection - origin).norm();

        if (dist < min_dist)
        {
            min_dist = dist;

            nearest_triangle_ptr = triangle;
            nearest_point = intersection;
        }
    }

    return nearest_triangle_ptr;
}