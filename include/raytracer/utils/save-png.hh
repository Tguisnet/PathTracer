#pragma once

#include <string>

#include <raytracer/types/image.hh>

namespace raytracer
{
    void save_png(const Image& image, const std::string& filename);
};