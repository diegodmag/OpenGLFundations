#include "Transformations.h"

glm::mat4 Transformations::buildTranslate(float x, float y, float z){
     glm::mat4 trans = glm::mat4( 1.0, 0.0, 0.0, 0.0,
                                  0.0, 1.0, 0.0, 0.0,
                                  0.0, 0.0, 1.0, 0.0,
                                  x, y, z, 1.0 );
                                  
                                    // This is the same as 
                                    //   1 0 0 x
                                    //   0 1 0 y
                                    //   0 0 1 z
                                    //   0 0 0 1
    return trans;
}

glm::mat4 Transformations::buildRotateX(float rad){
     glm::mat4 trans = glm::mat4( 1.0, 0.0, 0.0, 0.0,
                                  0.0, cos(rad), sin(rad), 0.0,
                                  0.0, -sin(rad), cos(rad), 0.0,
                                  0, 0, 0, 1.0 );

                                // This is the same as 
                                //   1 0 0 0
                                //   0 cos(rad) -sin(rad) y
                                //   0 sin(rad) cos(rad) z
                                //   0 0 0 1
    return trans;
}

glm::mat4 Transformations::buildRotateY(float rad){
     glm::mat4 trans = glm::mat4( cos(rad), 0.0, -sin(rad),0.0 ,
                                  0.0, 1, 0, 0.0,
                                  sin(rad), 0.0, cos(rad), 0.0,
                                  0, 0, 0, 1.0 );

                                // This is the same as 
                                //   cos(rad) 0 sin(rad) 0
                                //   0 1 0 0
                                //   -sin(rad) 0 cos(rad) z
                                //   0 0 0 1
    return trans;
}

glm::mat4 Transformations::buildRotateZ(float rad){
     glm::mat4 trans = glm::mat4( cos(rad), sin(rad), 0.0, 0.0,
                                  -sin(rad), cos(rad), 0, 0.0,
                                  0.0, 0.0, 1.0, 0.0,
                                  0, 0, 0, 1.0 );

                                // This is the same as 
                                //   cos(rad) -sin(rad) 0 0
                                //   sin(rad) cos(rad) 0 0
                                //   0 0 1 0
                                //   0 0 0 1
    return trans;
}