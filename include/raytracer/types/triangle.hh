#pragma once

#include <array>

#include <raytracer/types/vector.hh>

namespace raytracer
{
    struct Object;

    struct Triangle
    {
        struct KeyHasher
        {
            std::size_t operator()(const Triangle* k) const
            {
                return static_cast<unsigned>(k->idx);
            }
        };

        int idx;
        std::array<Vector, 3> vertices;
        std::array<Vector, 3> normals;
        const Object& object;

        bool operator==(const Triangle& other) const
        {
#ifndef NDEBUG
            if (idx != other.idx)
                return false;

            if (vertices[1] != other.vertices[1]
                || vertices[2] != other.vertices[2]
                || vertices[3] != other.vertices[3])
                throw std::runtime_error("Triangles with same idx have different vertices");

            return true;
#else
            return idx == other.idx;
#endif
        }

        Vector barycenter() const
        {
            return (vertices[0] + vertices[1] + vertices[2]) / 3.;
        }

        Vector normal(void) const;
    };
}
