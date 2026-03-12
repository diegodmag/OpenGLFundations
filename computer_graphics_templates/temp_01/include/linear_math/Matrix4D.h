#ifndef MATRIX4D_H
#define MATRIX4D_H

#include <iostream>
#include <cassert>
#include "linear_math/Vector4D.h"

namespace linear::math {
    struct Matrix4D {
    private:
        float arr_2D[4][4]{}; // 4 columnas, 4 filas

    public:
        Matrix4D() = default;

        // Constructor por filas (humano) -> almacenamiento por columnas (GPU)
        Matrix4D(float m00, float m01, float m02, float m03,
                 float m10, float m11, float m12, float m13,
                 float m20, float m21, float m22, float m23,
                 float m30, float m31, float m32, float m33) {
            arr_2D[0][0]=m00; arr_2D[1][0]=m01; arr_2D[2][0]=m02; arr_2D[3][0]=m03;
            arr_2D[0][1]=m10; arr_2D[1][1]=m11; arr_2D[2][1]=m12; arr_2D[3][1]=m13;
            arr_2D[0][2]=m20; arr_2D[1][2]=m21; arr_2D[2][2]=m22; arr_2D[3][2]=m23;
            arr_2D[0][3]=m30; arr_2D[1][3]=m31; arr_2D[2][3]=m32; arr_2D[3][3]=m33;
        }

        inline float& operator()(int i, int j) noexcept { return arr_2D[j][i]; }
        inline const float& operator()(int i, int j) const noexcept { return arr_2D[j][i]; }

        inline Vector4D& operator[](int j) noexcept {
            return *reinterpret_cast<Vector4D*>(arr_2D[j]);
        }

        const float* data() const noexcept { return &arr_2D[0][0]; }

        static Matrix4D Identity() noexcept {
            Matrix4D m;
            m(0,0)=1; m(1,1)=1; m(2,2)=1; m(3,3)=1;
            return m;
        }

        // --- Funciones de Transformación Reales ---

        static Matrix4D Translation(float x, float y, float z) noexcept {
            Matrix4D m = Identity();
            m(0,3) = x; m(1,3) = y; m(2,3) = z; // Columna 3, Filas 0,1,2
            return m;
        }

        static Matrix4D Scale(float x, float y, float z) noexcept {
            Matrix4D m = Identity();
            m(0,0) = x; m(1,1) = y; m(2,2) = z;
            return m;
        }
        // Agrega esto dentro de struct Matrix4D en Matrix4D.h
// En Matrix4D.h dentro de struct Matrix4D
        static Matrix4D Perspective(float fovDeg, float aspect, float nearP, float farP) noexcept {
            float fovRad = fovDeg * (3.1415926535f / 180.0f);
            float range = std::tan(fovRad / 2.0f) * nearP;
            float sx = (2.0f * nearP) / (range * aspect + range * aspect); // simplificable a nearP/(range*aspect)
            float sy = nearP / range;
            float sz = -(farP + nearP) / (farP - nearP);
            float pz = -(2.0f * farP * nearP) / (farP - nearP);

            Matrix4D m; // Inicializada en ceros
            m(0,0) = 1.0f / (aspect * std::tan(fovRad / 2.0f));
            m(1,1) = 1.0f / std::tan(fovRad / 2.0f);
            m(2,2) = -(farP + nearP) / (farP - nearP);
            m(2,3) = -1.0f; // Importante para la división de perspectiva
            m(3,2) = -(2.0f * farP * nearP) / (farP - nearP);
            m(3,3) = 0.0f;
            return m;
        }
    };

    // Multiplicación Matriz4x4 * Vector4D
    inline Vector4D operator*(const Matrix4D& m, const Vector4D& v) noexcept {
        return Vector4D{
            m(0,0)*v.x + m(0,1)*v.y + m(0,2)*v.z + m(0,3)*v.w,
            m(1,0)*v.x + m(1,1)*v.y + m(1,2)*v.z + m(1,3)*v.w,
            m(2,0)*v.x + m(2,1)*v.y + m(2,2)*v.z + m(2,3)*v.w,
            m(3,0)*v.x + m(3,1)*v.y + m(3,2)*v.z + m(3,3)*v.w
        };
    }

}


#endif