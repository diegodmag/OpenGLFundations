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
    linear::math::Matrix3D mat_1 {    1.0f, 2.0f, 3.0f,
                                    4.0f, 5.0f, 6.0f,
                                    7.0f, 8.0f, 9.0f,
    };

    linear::math::Matrix3D mat_2 {    1.0f, 2.0f, 3.0f,
                                    4.0f, 5.0f, 6.0f,
                                    7.0f, 8.0f, 9.0f,
    };


    std::cout<<mat_1<<"\n--------\n"; 
    // std::cout<<mat_2<<'\n'<<"="<<'\n'; 
    // // mat_1/=2; 
    // std::cout<<"--------"<<'\n'; 
    // linear::math::Matrix3D mat_product = mat_1*mat_2; 
    // std::cout<<mat_product<< '\n'; 
    // linear::math::Matrix3D mat_1_plus_2 = mat_1+mat_2;
    // std::cout<<mat_1_plus_2<<'\n';

    
    // Matrix times  vector 
    // linear::math::Vector3D v{5.0, 2.0, 3.0}; 
    // std::cout<<v<<'\n';
    // std::cout<<"---------"<<'\n';
    // std::cout<<mat_1*v<<'\n';

    linear::math::Matrix3D transpose = linear::math::Transpose(mat_1); 
    std::cout<<transpose<<'\n'; 
}

int main(){

    // testingVectors();

    // testingMatrix(); 

    Scene scene {};

    scene.render();

    return 0; 
}