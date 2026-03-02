#include "Scene.h"

#include "linear_math/Matrix3D.h"
#include "linear_math/Vector3D.h"

void testingVectors(){

    linear::math::Vector3D vec{}; 
    // linear::math::Matrix3D mat{};
    // std::cout<<vec<<'\n';

    std::cout<<linear::math::Normalize(vec)<<'\n';
}

void testingMatrix(){
    linear::math::Matrix3D mat {    1.0f, 2.0f, 3.0f,
                                    4.0f, 5.0f, 6.0f,
                                    7.0f, 8.0f, 9.0f,
    };
    std::cout<<mat<<'\n'; 
}

int main(){

    // testingVectors();

    testingMatrix(); 

    // Scene scene {};

    // scene.render();

    return 0; 
}