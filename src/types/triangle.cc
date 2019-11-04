#include <raytracer/types/triangle.hh>

using namespace raytracer;

Vector Triangle::normal(void) const
{
    Vector res = (vertices[1] - vertices[0]).cross(vertices[2] - vertices[0]);
    res.normalize();
    return res;
}
