#include <raytracer/kd-tree/traversal.hh>

#include <raytracer/kd-tree/kd-tree.hh>
#include <raytracer/types/triangle.hh>
#include <raytracer/types/vector.hh>

using namespace raytracer;

void raytracer::find_triangles(
        const KDTree::KDNode& node,
        const Vector& ray_origin,
        const Vector& ray,
        KDTree::TriangleSet& triangle_set
)
{
    // Check if ray intersects with the current node bounding box
    if (!node.aabb.intersects(ray_origin, ray))
        return;

    // Calls recursively the algorithm
    if (node.left)
        find_triangles(*node.left, ray_origin, ray, triangle_set);
    if (node.right)
        find_triangles(*node.right, ray_origin, ray, triangle_set);

    // Add all triangles to the set (no duplicates: the set handles them)
    triangle_set.insert(node.triangles.begin(), node.triangles.end());
}
