#include <raytracer/types/bsdf.hh>

#include <functional>
#include <unordered_map>

#include <raytracer/types/bsdfs/lambert-bsdf.hh>
#include <raytracer/types/bsdfs/mirror-bsdf.hh>
#include <raytracer/types/bsdfs/glass-bsdf.hh>
#include <raytracer/types/bsdfs/metal-bsdf.hh>
#include <raytracer/utils/math-utils.hh>

using namespace raytracer;

float BSDF::theta(const Vector& ray_dir, const Vector& u, const Vector& v, const Vector& w)
{
    return cartesian_to_spherical(change_basis(ray_dir, u, v, w))(1);
}

float BSDF::phi(const Vector& ray_dir, const Vector& u, const Vector& v, const Vector& w)
{
    return cartesian_to_spherical(change_basis(ray_dir, u, v, w))(2);
}

std::shared_ptr<BSDF> raytracer::bsdf_factory(const std::string& type)
{
    static const std::unordered_map<std::string, std::function<std::shared_ptr<BSDF>()>> factory = {
            {"lambert", [] () { return std::make_shared<LambertBSDF>(); }},
            {"mirror", [] () { return std::make_shared<MirrorBSDF>(); }},
            {"glass", [] () { return std::make_shared<GlassBSDF>(); }},
            {"metal", [] () { return std::make_shared<MetalBSDF>(); }}
    };

    return factory.at(type)();
}
