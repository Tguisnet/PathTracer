#include <raytracer/utils/math-utils.hh>

#include <cmath>

#include <raytracer/types/vector.hh>

using namespace raytracer;

// v is normalized
Vector raytracer::change_basis(const Vector& vec, const Vector& u, const Vector& v, const Vector& w)
{
    return Vector(vec.dot(u), vec.dot(v), vec.dot(w));
}

Vector raytracer::cartesian_to_spherical(const Vector &vec)
{
    float rho = vec.norm();
    float theta = std::atan2(vec.y(), vec.x());
    float phi = std::acos(vec.z() / rho);

    return Vector(rho, theta, phi);
}
