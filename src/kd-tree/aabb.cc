#include <raytracer/kd-tree/aabb.hh>

#include <algorithm>
#include <cmath>

#include <raytracer/constants.hh>
#include <raytracer/types/vector.hh>

using namespace raytracer;

float AABB::diagonal() const
{
    return (v_max - v_min).norm();
}

/*
 * Intersect ray R(t) = p + t*d against AABB a. When intersecting,
 *  provides intersection distance tmin and point q of intersection.
 *
 * Source: Real-Time Collision Detection (Christer Ericson, 2004)
 */
bool AABB::intersects(const Vector& p, const Vector& d) const
{
    float tmin = 0.0f; // set to -FLT_MAX to get first hit on line
    float tmax = FLT_MAX; // set to max distance ray can travel (for segment)

    // For all three slabs
    for (int i = 0; i < 3; i++)
    {
        if (std::abs(d[i]) < epsilon)
        {
            // Ray is parallel to slab. No hit if origin not within slab
            if (p[i] < v_min[i] || p[i] > v_max[i]) return false;
        }
        else
        {
            // Compute intersection t value of ray with near and far plane of slab
            float ood = 1.0f / d[i];
            float t1 = (v_min[i] - p[i]) * ood;
            float t2 = (v_max[i] - p[i]) * ood;

            // Make t1 be intersection with near plane, t2 with far plane
            if (t1 > t2) std::swap(t1, t2);

            // Compute the intersection of slab intersection intervals
            if (t1 > tmin) tmin = t1;
            if (t2 > tmax) tmax = t2;

            // Exit with no collision as soon as slab intersection becomes empty
            if (tmin > tmax) return false;
        }
    }

#if 0
    // Ray intersects all 3 slabs. Return point (q) and intersection t value (tmin)
    q = p + d * tmin;
#endif

    return true;
}
