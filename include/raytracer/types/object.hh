#pragma once

#include <cstddef>

#include <raytracer/types/bsdf.hh>
#include <raytracer/types/mesh.hh>
#include <raytracer/types/vector.hh>
#include <raytracer/utils/json-utils.hh>
#include <raytracer/utils/faces-range.hh>

namespace raytracer
{
    template <typename T>
    union Reference
    {
        T& operator*() { return *ptr; }
        const T& operator*() const { return *ptr; }
        T* operator->() { return ptr; }
        const T* operator->() const { return ptr; }

        std::size_t index;
        T* ptr;
    };

    struct Object
    {
        Reference<Mesh> mesh;
        Reference<BSDF> mtl;
        Vector position;
        Vector rotation;
        Vector scale;
        Vector emissive;

        const auto faces() const
        {
            return FacesRange(*this);
        }
    };

    template <typename T>
    static void from_json(const json& j, Reference<T>& mr)
    {
        j.get_to(mr.index);
    }

    static void from_json(const json& j, Object& o)
    {
        GET_TO(j, o, mesh);
        GET_TO(j, o, mtl);
        GET_TO(j, o, position);
        GET_TO(j, o, rotation);
        GET_TO(j, o, scale);

        o.emissive = j.value<Vector>("emissive", Vector::Zero());
    }
}
