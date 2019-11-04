#include <raytracer/types/bsdfs/lambert-bsdf.hh>

using namespace raytracer;

float LambertBSDF::density_phi(float x, const Vector& u, const Vector& v, const Vector& w, const Vector& ray_dir) const
{
	return x;
	//return 0.5 + std::sin(M_PI * x) / 2.f;
}

Vector LambertBSDF::radiance(const Vector& dir, const Vector& normal) const
{
    // Probability of the newRay
    auto p = 1.f / (2.f * M_PI);

    // Compute the BRDF for this ray (assuming Lambertian reflection)
    float cos_theta = -dir.dot(normal);
    Vector brdf = albedo / M_PI;

    return brdf * cos_theta / p;
}
