#pragma once

#include <raytracer/types/image.hh>
#include <raytracer/types/scene.hh>

namespace raytracer
{
    Image compute_screen(const Scene& scene);
};
