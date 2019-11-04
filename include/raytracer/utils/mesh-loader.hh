#pragma once

#include <string>

#include <raytracer/types/mesh.hh>

namespace raytracer
{
    Mesh load_mesh(const std::string& filename);
};
