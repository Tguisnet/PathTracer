#pragma once

#include <raytracer/kd-tree/kd-tree.hh>
#include <raytracer/types/triangle.hh>
#include <raytracer/types/vector.hh>

namespace raytracer
{
    void find_triangles(
            const KDTree::KDNode& node,
            const Vector& ray_origin,
            const Vector& ray,
            KDTree::TriangleSet& triangle_set
    );
}
