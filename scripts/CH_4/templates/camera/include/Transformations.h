#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Transformations
{
private:
    /* data */
public:
    static glm::mat4 buildTranslate(float x, float y, float z);
    static glm::mat4 buildRotateX(float rad);
    static glm::mat4 buildRotateY(float rad);
    static glm::mat4 buildRotateZ(float rad);
    
};


#endif