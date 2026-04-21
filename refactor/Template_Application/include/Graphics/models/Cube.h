#ifndef CUBE_H
#define CUBE_H

#include "Graphics/Model.h"

class Cube : public Model
{
private:
    GLfloat vertices[48];
    GLuint indices[36];

public:
    Cube(std::shared_ptr<ShaderProgram> program) : Model(program)
    {

        initGeometry();

        init();
    }

    ~Cube() override; 

    void initGeometry() override;

    void init() override;

    void translate(const linear::math::Vector3D &translation) override;

    void rotate(float angle, const linear::math::Vector3D &axis) override;

    void scale(const linear::math::Vector3D &scaling) override;

    void renderModel(const linear::math::Matrix4D &view, const linear::math::Matrix4D &projection) override;

    void updateModel(float deltaTime) override;

    // void finish() override;
};

#endif