#ifndef VECTOR4D_H
#define VECTOR4D_H

#include <iostream>
#include <cmath>
#include <cassert>

#include "linear_math/Vector3D.h"

namespace linear::math {
    struct Vector4D {
        float x{0.0f}, y{0.0f}, z{0.0f}, w{1.0f}; // w suele ser 1.0 para puntos

        Vector4D() = default;
        Vector4D(float a, float b, float c, float d = 1.0f) : x{a}, y{b}, z{c}, w{d} {}
        
        // Constructor desde Vector3D (Útil para convertir puntos 3D a 4D)
        Vector4D(const Vector3D& v, float d = 1.0f) : x{v.x}, y{v.y}, z{v.z}, w{d} {}

        inline float& operator[](int i) noexcept {
            assert(i >= 0 && i <= 3);
            return (&x)[i];
        }

        inline const float& operator[](int i) const noexcept {
            assert(i >= 0 && i <= 3);
            return (&x)[i];
        }
    };
}

#endif