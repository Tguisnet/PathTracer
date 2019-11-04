#include <raytracer/constants.hh>
#include <raytracer/types/bsdfs/glass-bsdf.hh>

using namespace raytracer;

Vector GlassBSDF::radiance(const Vector& dir, const Vector& normal) const
{
    Vector brdf = albedo;

    return brdf;
}

float GlassBSDF::density_theta(float, const Vector& u, const Vector& v, const Vector& w, const Vector& ray_dir) const
{
    float theta_prime = theta(ray_dir, u, v, w) + M_PI;

    return fmod(theta_prime / (2.f * M_PI), 1.f);
}

float GlassBSDF::density_phi(float t, const Vector& u, const Vector& v, const Vector& w, const Vector& ray_dir) const
{
    float phi_prime = phi(ray_dir, u, v, w);

    if (t > .3)
        phi_prime = M_PI - phi_prime;

    return fmod(phi_prime / M_PI, 1.f);
}