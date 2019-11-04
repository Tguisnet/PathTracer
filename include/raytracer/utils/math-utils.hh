#pragma once

#include <raytracer/types/vector.hh>

namespace raytracer {
    Vector change_basis(const Vector &vec, const Vector &u, const Vector &v, const Vector &w);
    Vector cartesian_to_spherical(const Vector &vec);
}
