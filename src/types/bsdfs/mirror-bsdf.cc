#include <raytracer/constants.hh>
#include <raytracer/types/bsdfs/mirror-bsdf.hh>

using namespace raytracer;

Vector MirrorBSDF::radiance(const Vector& dir, const Vector& normal) const
{
    Vector brdf = albedo;

    return brdf;
}

float MirrorBSDF::density_theta(float, const Vector& u, const Vector& v, const Vector& w, const Vector& ray_dir) const
{
    float theta_prime = theta(ray_dir, u, v, w) + M_PI;

    return fmod(theta_prime / (2.f * M_PI), 1.f);
}

float MirrorBSDF::density_phi(float, const Vector& u, const Vector& v, const Vector& w, const Vector& ray_dir) const
{
    float phi_prime = phi(ray_dir, u, v, w);

    return fmod(phi_prime / M_PI, 1.f);
}
