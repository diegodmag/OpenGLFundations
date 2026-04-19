#ifndef APPLICATION_H
#define APPLICATION_H

#include <memory>

#include "Core/WindowGL.h"
#include "Core/Scene.h"

class Application
{
private:
    std::unique_ptr<WindowGL> m_window;
    std::unique_ptr<Scene> m_scene;
    /* data */
public:
    Application();
    ~Application();

    void run();
};

#endif