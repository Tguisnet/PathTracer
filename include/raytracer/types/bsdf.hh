#pragma once

#include <memory>
#include <string>

#include <raytracer/types/vector.hh>

namespace raytracer
{
    struct BSDF
    {
        static float theta(const Vector& ray_dir, const Vector& u, const Vector& v, const Vector& w);
        static float phi(const Vector& ray_dir, const Vector& u, const Vector& v, const Vector& w);

        virtual Vector radiance(const Vector& dir, const Vector& normal) const = 0;
        virtual float density_theta(float x, const Vector& u, const Vector& v, const Vector& w, const Vector& ray_dir) const = 0;
        virtual float density_phi(float x, const Vector& u, const Vector& v, const Vector& w, const Vector& ray_dir) const { return x; }
        virtual void load_from_json(const json& j) = 0;
    };

    std::shared_ptr<BSDF> bsdf_factory(const std::string& type);

    static void from_json(const json& j, BSDF& b)
    {
        b.load_from_json(j);
    }

    static void from_json(const json& j, std::shared_ptr<BSDF>& b)
    {
        if (j.is_string())
        {
            from_json(parse_json(j.get<std::string>().c_str()), b);
            return;
        }

        b = bsdf_factory(j.at("type").get<std::string>());
        j.get_to(*b);
    }
}
