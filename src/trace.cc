#include <raytracer/trace.hh>

#include <cstddef>
#include <random>

#include <raytracer/constants.hh>
#include <raytracer/intersect.hh>
#include <raytracer/kd-tree/kd-tree.hh>
#include <raytracer/types/scene.hh>
#include <raytracer/types/vector.hh>
#include <raytracer/types/bsdfs/lambert-bsdf.hh>

using namespace raytracer;

static thread_local std::random_device rd;
static thread_local std::mt19937 gen(rd());

// Source: Realistic Ray Tracing (Shirley and Morley)
/*static Vector ray_direction(const Vector& dir, const Vector& normal)
{
    //return (Vector(-0.005, 1.98, -0.03) - intersection).normalized();

    std::uniform_real_distribution<> dis(0.f, 1.f);

    float r1 = 2*M_PI*dis(gen);
    float r2 = dis(gen);
    float r2s = std::sqrt(r2);

    const Vector& w = normal;
    Vector u = ((std::abs(w(0))>.1?Vector(0,1,0):Vector(1,0,0)).cross(w)).normalized();
    Vector v = w.cross(u);

    return (u*std::cos(r1)*r2s + v*std::sin(r1)*r2s + w*std::sqrt(1-r2)).normalized();
}*/

static Vector ray_direction(const Triangle& triangle, const Vector& w, const BSDF& bsdf, const Vector& ray_dir)
{
    std::uniform_real_distribution<> dis(0.f, 1.f);

    Vector u = (triangle.vertices[1] - triangle.vertices[0]).normalized();
    Vector v = (triangle.vertices[2] - triangle.vertices[0]).normalized();

    v -= u.dot(v) * u;
    v.normalize();

    if (u.cross(v).dot(w) < 0)
        std::swap(u, v);

    auto theta = bsdf.density_theta(dis(gen), u, v, w, - ray_dir) * 2.f * M_PI;
    auto phi = bsdf.density_phi(dis(gen), u, v, w, - ray_dir) * M_PI;

    return (std::sin(phi) * std::cos(theta) * u) + (std::sin(phi) * std::sin(theta) * v) + (std::cos(phi) * w);
}

Vector raytracer::trace(const KDTree& kd_tree, const Vector& ray_o, const Vector& ray_dir, std::size_t spp, std::size_t max_depth)
{
    if (!max_depth)
        return Vector::Zero();

    Vector intersection;
    auto triangle = nearest_triangle(ray_o, kd_tree, ray_dir, intersection);

    // No intersection, return no light
    if (!triangle)
        return Vector::Zero();

    Vector normal = triangle->normal();
    if (normal.dot(ray_dir) > 0)
        normal *= -1.f;
    const auto& bsdf = *triangle->object.mtl;

    Vector color = Vector::Zero();
    for (std::size_t i = 0; i < spp; ++i)
    {
        //Vector dir = ray_direction(dir, normal);
        Vector dir = ray_direction(*triangle, normal, bsdf, ray_dir);
        color += trace(kd_tree, intersection + dir * 0.0001, dir, spp, max_depth - 1).cwiseProduct(
                bsdf.radiance(dir, (normal.dot(dir) > 0) ? -normal : normal)).unaryExpr([] (auto x) { return std::max(0.f, x); });
    }

    return (triangle->object.emissive + (color / spp)).unaryExpr([] (auto x) { return std::max(0.f, x); });
}
