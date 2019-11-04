#pragma once

#include <cstdio>
#include <vector>

#include <raytracer/types/pixel.hh>
#include <raytracer/types/vector.hh>

namespace raytracer
{
    class Image {

    public:
        Image(const std::size_t width, const std::size_t height);

        const std::vector<unsigned char>& data() const;

        const std::size_t width() const;

        const std::size_t height() const;

        void set_pixel(std::size_t x, std::size_t y, Pixel p);

        void set_pixel(std::size_t x, std::size_t y, const Vector& color);

    private:
        std::vector<unsigned char> data_;
        const std::size_t width_;
        const std::size_t height_;
    };
}