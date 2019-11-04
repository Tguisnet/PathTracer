#include <raytracer/types/image.hh>

#include <string>
#include <stdexcept>
#include <iostream>

using namespace raytracer;

Image::Image(const std::size_t width, const std::size_t height)
    : width_(width)
    , height_(height)
    , data_(width * height * 4, 0)
{
}

const std::vector<unsigned char>& Image::data() const
{
    return data_;
}

const std::size_t Image::width() const
{
    return width_;
}

const std::size_t Image::height() const
{
    return height_;
}

void Image::set_pixel(std::size_t x, std::size_t y, Pixel p)
{
    if (x >= width_ || y >= height_)
        throw std::out_of_range("Coordinates outside the picture");

    std::size_t index = (y * width_ + x) * 4;
    data_[index] = p.r;
    data_[index + 1] = p.g;
    data_[index + 2] = p.b;
    data_[index + 3] = p.a;
}

void Image::set_pixel(std::size_t x, std::size_t y, const Vector& color)
{
    set_pixel(x, y, Pixel{
            static_cast<unsigned char>(round(color[0] * 255)),
            static_cast<unsigned char>(round(color[1] * 255)),
            static_cast<unsigned char>(round(color[2] * 255)),
            255
    });
}