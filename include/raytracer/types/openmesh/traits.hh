#pragma once

#include <Eigen/Dense>

// Should be included before
#include <OpenMesh/Core/Utils/vector_traits.hh>

#include <OpenMesh/Core/Geometry/EigenVectorT.hh>
#include <OpenMesh/Core/Mesh/Traits.hh>

namespace raytracer
{
    struct EigenTraits : OpenMesh::DefaultTraits
    {
        using Point = Eigen::Vector3f;
        using Normal = Point;
        using Color = Eigen::Matrix<unsigned char, 3, 1>;

        using TexCoord2D = Eigen::Vector2f;
    };

    using OpenMeshTraits = EigenTraits;
}
