#pragma once

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

    void DrawMenuBar();
    void DrawSidebar();
    void DrawMainContent();
    void DrawStatusBar();

    void DrawDashboard();
    void DrawEngine();
    void DrawAnalysis();
    void DrawResults();

    Page m_currentPage = Page::Dashboard;
};