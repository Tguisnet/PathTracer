#include <raytracer/utils/save-png.hh>

#include <iostream>
#include <stdexcept>
#include <string>

#include <lodepng.h>


using namespace raytracer;


void raytracer::save_png(const Image& image, const std::string& filename)
{
    /* LodePNG library should expect a non-constant vector but does not, so let's const_cast it */
    unsigned error = lodepng::encode(filename, const_cast<std::vector<unsigned char>&>(image.data()), image.width(), image.height(), LCT_RGBA);

    if(error) throw std::runtime_error(std::string("Encoder Error : ") + lodepng_error_text(error));
}