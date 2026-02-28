#include "Scene.h"

#include "linear_math/Matrix3D.h"
#include "linear_math/Vector3D.h"

void testingVectors(){

    linear::math::Vector3D vec{}; 
    // linear::math::Matrix3D mat{};
    // std::cout<<vec<<'\n';

    std::cout<<linear::math::Normalize(vec)<<'\n';
}

int main(){

    testingVectors();

    Scene scene {};

    scene.render();

    return 0; 
}