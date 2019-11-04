#pragma once

#include <raytracer/types/vector.hh>

namespace raytracer
{
    // Axis-aligned bounding box
    struct AABB
    {
        Vector v_min;
        Vector v_max;

        float diagonal() const;

        bool intersects(const Vector& p, const Vector& d) const;
    };
}
