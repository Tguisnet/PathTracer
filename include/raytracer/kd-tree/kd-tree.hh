#pragma once

#include <cstdint>
#include <memory>
#include <unordered_set>
#include <vector>

#include <raytracer/kd-tree/aabb.hh>
#include <raytracer/types/triangle.hh>
#include <raytracer/types/vector.hh>

namespace raytracer
{
    class KDTree
    {
        struct Node
        {
            AABB aabb;
            std::shared_ptr<Node> left;
            std::shared_ptr<Node> right;
            std::vector<const Triangle*> triangles;
        };

    public:
        using KDNode = Node;
        using TriangleSet = std::unordered_set<const Triangle*, Triangle::KeyHasher>;

        KDTree() = delete;
        KDTree(const KDTree&) = delete;
        KDTree& operator=(const KDTree&) = delete;

        explicit KDTree(std::vector<Triangle>&& triangles);

        TriangleSet intersect(const Vector& ray_origin, const Vector& ray) const;

    private:
        std::vector<Triangle> triangles_;
        std::shared_ptr<Node> root_;
    };
}
