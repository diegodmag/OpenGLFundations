#ifndef MATRIX3D_H
#define MATRIX3D_H

#include <iostream>
#include <cassert>
#include "Vector3D.h"

namespace linear::math{

    struct Matrix3D
    {
        private: 
            float arr_2D[3][3]; 

        public: 
        /* data */
        Matrix3D() = default;

        Matrix3D(   float m_00, float m_01, float m_02,
                    float m_10, float m_11, float m_12, 
                    float m_20, float m_21, float m_22
        ):          arr_2D{ {m_00, m_10, m_20},
                            {m_01, m_11, m_21},
                            {m_02, m_12, m_22}}{} // Column major order 
        
        /// @brief Matrix3D constructor from 3 3D vectors 
        /// @param a 
        /// @param b 
        /// @param c 
        Matrix3D(   linear::math::Vector3D& a,
                    linear::math::Vector3D& b,
                    linear::math::Vector3D& c 
        ):          arr_2D{ {a.x, a.y, a.z},
                            {b.x, b.y, b.z},
                            {c.x, c.y, c.z}}{}


        inline float& operator()(int i, int j){
            // To keep doing it as the math model 
            assert(0<= i && i<=2); 
            assert(0<= j && j<=2);
            // return arr_ 
            return arr_2D[j][i]; 
        }

        inline const float& operator()(int i, int j)const{
            // To keep doing it as the math model 
            assert(0<= i && i<=2); 
            assert(0<= j && j<=2);
            // return arr_ 
            return arr_2D[j][i]; 
        }

        // 
        Vector3D operator[](int i){
            return Vector3D{arr_2D[0][i],arr_2D[1][i], arr_2D[2][i]}; 
        }
        
        inline friend std::ostream& operator<<(std::ostream& os, Matrix3D& v){
            os  << "["  <<  " " << v(0,0) << ", " << v(1,0) << ", " << v(2,0) <<'\n' 
                        <<  "  " << v(0,1) << ", " << v(1,1) << ", " << v(2,1) <<'\n'
                        <<  "  " << v(0,2) << ", " << v(1,2) << ", " << v(2,2) << " " << "]"; 
            return  os; 
        }
        // Basics operations 
    };
    
    // Matrix3D operator+(const Matrix3D& a, const Matrix3D& b){
    //     return Matrix3D{    a(0,1)-b(0,1), a(0,1)-b(0,1), a(0,1)-b(0,1), 
    //                         a(0,1)-b(0,1), a(0,1)-b(0,1), a(0,1)-b(0,1), 
    //                         a(0,1)-b(0,1), a(0,1)-b(0,1), a(0,1)-b(0,1) 
    //     }; 

    // }
};

#endif 