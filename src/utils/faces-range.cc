#include <raytracer/utils/faces-range.hh>

#include <algorithm>
#include <cstddef>
#include <iterator>

#include <Eigen/Dense>
#include <raytracer/types/object.hh>
#include <raytracer/types/triangle.hh>

using namespace raytracer;

static auto rotYXZ(const Vector& r)
{
    float c[] = {std::cos(r.x()), std::cos(r.y()), std::cos(r.z())};
    float s[] = {std::sin(r.x()), std::sin(r.y()), std::sin(r.z())};

    auto mat =  Eigen::Matrix3f();
    mat << c[1] * c[2] - s[1] * s[0] * s[2], -c[1] * s[2] - s[1] * s[0] * c[2], -s[1] * c[0],
    c[0] * s[2], c[0] * c[2], -s[0],
    s[1] * c[2] + c[1] * s[0] * s[2], -s[1] * s[2] + c[1] * s[0] * c[2], c[1] * c[0];
    return mat;
}

Triangle FacesRange::FacesIterator::operator*() const
{
    std::vector<Vector> vertices;
    std::vector<Vector> normals;
    const auto& mesh = *object_.mesh;
    const auto& fh = *iter_;

    for (const auto& vh: mesh.fv_range(fh))
    {
        vertices.push_back(mesh.point(vh));
        normals.push_back(mesh.normal(vh));
    }

#ifndef NDEBUG
    /*
     * In theory, polygons (faces with more than 3 edges) cannot
     * exist due to the mesh triangulation (c.f. mesh-loader.cc).
     */
    if (vertices.size() != 3)
        throw std::runtime_error(
                "Face contains " + std::to_string(vertices.size())
                + " vertices (expecting 3)");
#endif

    // A transformation is a scaling and a 3-axis rotation
    Vector rotation_vec = object_.rotation / 180.f * M_PI;
    Eigen::Matrix3f rotation = rotYXZ(rotation_vec);
    Eigen::Matrix3f transformation = rotation * Eigen::Scaling(object_.scale);

    const auto& translation = object_.position;

    // Applying object transformation to the vertices
    std::transform(vertices.begin(), vertices.end(),
                   vertices.begin(),
                   [&transformation, &translation](const auto& vertex)
                   {
                       return transformation * vertex + translation;
                   });

    // Applying object rotation to the normals
    std::transform(normals.begin(), normals.end(),
                   normals.begin(),
                   [&rotation](const auto& vertex)
                   {
                       return rotation * vertex;
                   });

    return Triangle{
            fh.idx(),
            vertices[0], vertices[1], vertices[2],
            normals[0], normals[1], normals[2],
            object_
    };
}

FacesRange::FacesIterator FacesRange::begin() const
{
    return FacesIterator(object_, (*object_.mesh).faces_sbegin());
}

FacesRange::FacesIterator FacesRange::end() const
{
    return FacesIterator(object_, (*object_.mesh).faces_end());
}
