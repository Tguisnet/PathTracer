#pragma once

#include <raytracer/kd-tree/kd-tree.hh>
#include <raytracer/types/scene.hh>
#include <raytracer/types/vector.hh>

namespace raytracer
{
    Vector trace(const KDTree& kd_tree, const Vector& ray_o, const Vector& ray_dir, std::size_t spp, std::size_t max_depth);
}
