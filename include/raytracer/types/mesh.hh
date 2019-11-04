#pragma once

#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
#include <raytracer/types/openmesh/traits.hh>
#include <raytracer/utils/json-utils.hh>

namespace raytracer
{
    using Mesh = OpenMesh::TriMesh_ArrayKernelT<OpenMeshTraits>;

    void from_json(const json& j, Mesh& m);
};
