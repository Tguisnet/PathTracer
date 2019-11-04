#pragma once

#include <raytracer/types/bsdf.hh>
#include <raytracer/types/vector.hh>

namespace raytracer
{
    struct LambertBSDF: BSDF
    {
        Vector albedo;

        Vector radiance(const Vector& dir, const Vector& normal) const override;

        float density_theta(float x, const Vector& u, const Vector& v, const Vector& w, const Vector& ray_dir) const override { return x; }
        float density_phi(float x, const Vector& u, const Vector& v, const Vector& w, const Vector& ray_dir) const override;

        void load_from_json(const json& j) override
        {
            GET_TO(j, *this, albedo);
        }
    };
};
