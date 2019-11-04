#include <raytracer/types/image.hh>
#include <raytracer/utils/save-png.hh>
#include <lodepng.h>

using namespace raytracer;

int main(int argc, char **argv)
{
    Image img = Image(10, 10);

    struct Pixel p = {.r = 0, .g = 0, .b = 255, .a = 255};

    img.set_pixel(0,0,p);
    img.set_pixel(0,1,p);
    img.set_pixel(1,0,p);
    img.set_pixel(9,9,p);
    img.set_pixel(8,9,p);

    save_png(img, "test_save_image.png");

    return 0;
}