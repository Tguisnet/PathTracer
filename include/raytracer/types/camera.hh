#pragma once

#include <raytracer/types/vector.hh>
#include <raytracer/utils/json-utils.hh>

namespace raytracer
{
    struct Camera
    {
        Vector pos;
        Vector forward;
        Vector up;
        float fov;
    };

    static void from_json(const json& j, Camera& c)
    {
        GET_TO(j, c, pos);
        GET_TO(j, c, forward);
        GET_TO(j, c, up);
        GET_TO(j, c, fov);
    }
}
