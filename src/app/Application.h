#pragma once

#include "../simulation/Simulation.h"

struct GLFWwindow;

class GUI;

class Application
{
public:
    Application();
    ~Application();


    int Run();

private:
    bool Initialize();
    void Shutdown();

    void BeginFrame();
    void EndFrame();

    GLFWwindow* m_window = nullptr;
    GUI* m_gui = nullptr;

    Simulation m_simulation;

};