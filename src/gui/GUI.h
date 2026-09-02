#pragma once
#include "imgui.h"
#include "./simulation/Simulation.h"
#include <vector>

class Simulation;
class GUI
{
public:
    explicit GUI(Simulation& simulation);

    GUI();
    ~GUI();

    void Draw();

private:
    Simulation& m_simulation;
    enum class Page
    {
        Dashboard,
        Engine,
        Analysis,
        Results
    };

    std::vector<float> m_altitudes;
    std::vector<float> m_thrusts;

    void DrawMenuBar();
    void DrawSidebar();
    void DrawViewport();
    void DrawResults();
    void DrawAnalysis();
    void DrawThrustAnalysis();
    void RunThrustAnalysis();

    ImFont* m_interRegular = nullptr;
    ImFont* m_interMedium = nullptr;
    ImFont* m_interSemiBold = nullptr;

};