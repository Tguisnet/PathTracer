#pragma once

#include <cstddef>
#include <vector>

#include <raytracer/kd-tree/kd-tree.hh>
#include <raytracer/types/triangle.hh>

namespace raytracer
{
    std::shared_ptr<KDTree::KDNode> build_kdtree(std::vector<const Triangle*> triangles, std::size_t depth = 0);
}
