#pragma once

#include <cstddef>
#include <memory>
#include <string>
#include <vector>

#include <raytracer/types/camera.hh>
#include <raytracer/types/object.hh>
#include <raytracer/types/bsdf.hh>
#include <raytracer/utils/json-utils.hh>

namespace raytracer
{
    static inline auto sum_meshes(
            const std::vector<Mesh>& meshes,
            std::function<std::size_t(const Mesh&)> count_fct
            )
    {
            return std::accumulate(
                    meshes.begin(),
                    meshes.end(),
                    0,
                    [&count_fct](auto sum, const auto& mesh) {
                        return sum + count_fct(mesh);
                    }
            );
    }

    struct Scene
    {
        std::size_t width;
        std::size_t height;
        Camera camera;
        std::vector<Mesh> meshes;
        std::vector<std::shared_ptr<BSDF>> materials;
        std::vector<Object> objects;

        auto n_vertices()
        {
            return sum_meshes(
                    meshes,
                    [](const auto& mesh) {
                        return mesh.n_vertices();
                    }
            );
        }

        auto n_faces()
        {
            return sum_meshes(
                    meshes,
                    [](const auto& mesh) {
                        return mesh.n_faces();
                    }
            );
        }
    };

    static void from_json(const json& j, Scene& s)
    {
        GET_TO(j, s, width);
        GET_TO(j, s, height);
        GET_TO(j, s, camera);

        if (j.find("meshs") != j.end())
            GET_TO_OTHER(j, s, "meshs", meshes);
        else
            GET_TO(j, s, meshes);

        GET_TO(j, s, materials);
        GET_TO(j, s, objects);

        for (auto& obj: s.objects)
        {
            obj.mesh.ptr = &s.meshes[obj.mesh.index];
            obj.mtl.ptr = s.materials[obj.mtl.index].get();
        }
    }
}
