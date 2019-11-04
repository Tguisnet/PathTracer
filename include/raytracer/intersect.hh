#pragma once

#include <raytracer/kd-tree/kd-tree.hh>
#include <raytracer/types/triangle.hh>
#include <raytracer/types/vector.hh>

namespace raytracer
{
    const Triangle* nearest_triangle(
            const Vector& origin,
            const KDTree& kd_tree,
            const Vector& ray,
            Vector& nearest_point
    );
}