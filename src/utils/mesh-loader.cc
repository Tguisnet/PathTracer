#include <raytracer/utils/mesh-loader.hh>

#include <stdexcept>
#include <string>

#include <OpenMesh/Core/IO/MeshIO.hh>
#include <raytracer/types/mesh.hh>

using namespace raytracer;

Mesh raytracer::load_mesh(const std::string& filename)
{
    Mesh mesh;

    // Requesting basic features for the mesh
    mesh.request_vertex_normals();
    mesh.request_face_normals();

    // Loading the mesh from the object file
    using MeshOptions = OpenMesh::IO::Options;
    OpenMesh::IO::Options read_options =
            MeshOptions::VertexNormal
            | MeshOptions::FaceNormal;

    if (!OpenMesh::IO::read_mesh(mesh, filename, read_options))
        throw std::runtime_error("Failed to load mesh");

    // Compute vertices normals
    if (!read_options.check(OpenMesh::IO::Options::VertexNormal))
    {
        if (!read_options.check(OpenMesh::IO::Options::FaceNormal))
            mesh.update_face_normals();

        mesh.update_vertex_normals();
    }

    // Triangulate all polygonal faces (split them in multiple triangular faces)
    mesh.triangulate();

    return mesh;
}

void raytracer::from_json(const json& j, Mesh& m)
{
    m = load_mesh(j.get<std::string>());
}
