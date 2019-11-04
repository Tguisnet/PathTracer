#include <raytracer/constants.hh>
#include <raytracer/types/bsdfs/metal-bsdf.hh>

using namespace raytracer;

static constexpr float diffuse = 0.15;
static constexpr float specular = 0.85;

Vector MetalBSDF::radiance(const Vector& dir, const Vector& normal) const
{
    // Probability of the newRay
    auto p = 1.f / (2.f * M_PI);

    // Compute the BRDF for this ray (assuming Lambertian reflection)
    float cos_theta = -dir.dot(normal);
    Vector brdf = albedo / M_PI;

    Vector res = (brdf * cos_theta / p) * diffuse + albedo * specular;

    return res;
}

float MetalBSDF::density_theta(float t, const Vector& u, const Vector& v, const Vector& w, const Vector& ray_dir) const
{
    float theta_prime = theta(ray_dir, u, v, w) + M_PI;

    return (fmod(theta_prime / (2.f * M_PI), 1.f)) * specular + diffuse * t;
}

float MetalBSDF::density_phi(float t, const Vector& u, const Vector& v, const Vector& w, const Vector& ray_dir) const
{
    float phi_prime = phi(ray_dir, u, v, w);

    return (fmod(phi_prime / M_PI, 1.f)) * specular + t * diffuse;
}
