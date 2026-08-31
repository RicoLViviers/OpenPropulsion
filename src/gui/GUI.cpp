#include "GUI.h"

#include "imgui.h"

GUI::GUI(Simulation& simulation) : m_simulation(simulation)
{
}

GUI::~GUI()
{
}

void GUI::Draw()
{
    DrawMenuBar();
    DrawSidebar();
    DrawMainContent();
    DrawStatusBar();
}

void GUI::DrawMenuBar()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            ImGui::MenuItem("New Project");
            ImGui::MenuItem("Open Project");
            ImGui::MenuItem("Save Project");

            ImGui::Separator();

            if (ImGui::MenuItem("Exit"))
            {
                // We will handle application shutdown later.
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Simulation"))
        {
            ImGui::MenuItem("Run");
            ImGui::MenuItem("Pause");
            ImGui::MenuItem("Reset");

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("View"))
        {
            ImGui::MenuItem("Dashboard");
            ImGui::MenuItem("Engine");
            ImGui::MenuItem("Analysis");
            ImGui::MenuItem("Results");

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Help"))
        {
            ImGui::MenuItem("Documentation");
            ImGui::MenuItem("About OpenPropulsion");

            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
}

void GUI::DrawSidebar()
{
    ImGuiViewport* viewport = ImGui::GetMainViewport();

    const float menuBarHeight = ImGui::GetFrameHeight();
    const float statusBarHeight = 28.0f;
    const float sidebarWidth = 220.0f;

    ImGui::SetNextWindowPos(
        ImVec2(viewport->Pos.x, viewport->Pos.y + menuBarHeight)
    );

    ImGui::SetNextWindowSize(
        ImVec2(
            sidebarWidth,
            viewport->Size.y - menuBarHeight - statusBarHeight
        )
    );

    ImGuiWindowFlags flags =
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoCollapse;

    ImGui::Begin("Sidebar", nullptr, flags);

    ImGui::Spacing();

    ImGui::Text("OPENPROPULSION");

    ImGui::Separator();

    ImGui::Spacing();

    if (ImGui::Selectable(
        "Dashboard",
        m_currentPage == Page::Dashboard
    ))
    {
        m_currentPage = Page::Dashboard;
    }

    if (ImGui::Selectable(
        "Engine",
        m_currentPage == Page::Engine
    ))
    {
        m_currentPage = Page::Engine;
    }

    if (ImGui::Selectable(
        "Analysis",
        m_currentPage == Page::Analysis
    ))
    {
        m_currentPage = Page::Analysis;
    }

    if (ImGui::Selectable(
        "Results",
        m_currentPage == Page::Results
    ))
    {
        m_currentPage = Page::Results;
    }

    ImGui::End();
}


void GUI::DrawMainContent()
{
    ImGuiViewport* viewport = ImGui::GetMainViewport();

    const float menuBarHeight = ImGui::GetFrameHeight();
    const float statusBarHeight = 28.0f;
    const float sidebarWidth = 220.0f;

    ImGui::SetNextWindowPos(
        ImVec2(
            viewport->Pos.x + sidebarWidth,
            viewport->Pos.y + menuBarHeight
        )
    );

    ImGui::SetNextWindowSize(
        ImVec2(
            viewport->Size.x - sidebarWidth,
            viewport->Size.y - menuBarHeight - statusBarHeight
        )
    );

    ImGuiWindowFlags flags =
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoCollapse;

    ImGui::Begin("Main Content", nullptr, flags);

    switch (m_currentPage)
    {
        case Page::Dashboard:
            DrawDashboard();
            break;

        case Page::Engine:
            DrawEngine();
            break;

        case Page::Analysis:
            DrawAnalysis();
            break;

        case Page::Results:
            DrawResults();
            break;
    }

    ImGui::End();
}


void GUI::DrawDashboard()
{
    ImGui::Text("Dashboard");

    ImGui::Separator();

    ImGui::Spacing();

    ImGui::Text("Welcome to OpenPropulsion.");
    ImGui::Text(
        "Gas turbine and propulsion performance analysis."
    );

    ImGui::Spacing();
    ImGui::Spacing();

    if (ImGui::Button("New Engine", ImVec2(150, 40)))
    {
        m_currentPage = Page::Engine;
    }

    ImGui::SameLine();

    if (ImGui::Button("Open Analysis", ImVec2(150, 40)))
    {
        m_currentPage = Page::Analysis;
    }

    ImGui::Spacing();
    ImGui::Spacing();

    ImGui::Text("Project Status");

    ImGui::Separator();

    ImGui::BulletText("Engine: Not configured");
    ImGui::BulletText("Simulation: Ready");
    ImGui::BulletText("Results: No data");
}

void GUI::DrawEngine()
{
    ImGui::Text("Engine Configuration");

    ImGui::Separator();

    ImGui::Spacing();

    static float pressureRatio = 10.0f;
    static float massFlow = 5.0f;
    static float turbineInletTemperature = 1200.0f;

    ImGui::Text("Compressor");

    ImGui::SliderFloat(
        "Pressure Ratio",
        &pressureRatio,
        1.0f,
        50.0f
    );

    ImGui::Spacing();

    ImGui::Text("Mass Flow");

    ImGui::SliderFloat(
        "Mass Flow (kg/s)",
        &massFlow,
        0.1f,
        100.0f
    );

    ImGui::Spacing();

    ImGui::Text("Combustor");

    ImGui::SliderFloat(
        "Turbine Inlet Temperature (K)",
        &turbineInletTemperature,
        500.0f,
        2000.0f
    );

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    if (ImGui::Button("Run Simulation", ImVec2(160, 40)))
    {
        m_currentPage = Page::Results;
    }
}

void GUI::DrawAnalysis()
{
    ImGui::Text("Performance Analysis");

    ImGui::Separator();

    ImGui::Spacing();

    ImGui::Text("Performance Charts");

    ImGui::BeginChild(
        "ChartArea",
        ImVec2(0, 300),
        true
    );

    ImGui::Text(
        "Charts will be implemented here."
    );

    ImGui::EndChild();

    ImGui::Spacing();

    ImGui::Text("Analysis Parameters");

    ImGui::BulletText("Pressure ratio");
    ImGui::BulletText("Mass flow");
    ImGui::BulletText("Temperature");
    ImGui::BulletText("Thrust");
}

void GUI::DrawResults()
{
    ImGui::Text("Simulation Results");

    ImGui::Separator();

    ImGui::Spacing();

    ImGui::Text("Engine Performance");

    ImGui::Separator();

    ImGui::Text("Thrust:");
    ImGui::SameLine(250);
    ImGui::Text("0.00 N");

    ImGui::Text("Specific Fuel Consumption:");
    ImGui::SameLine(250);
    ImGui::Text("0.000 kg/N/s");

    ImGui::Text("Overall Pressure Ratio:");
    ImGui::SameLine(250);
    ImGui::Text("0.00");

    ImGui::Text("Thermal Efficiency:");
    ImGui::SameLine(250);
    ImGui::Text("0.00 %%");

    ImGui::Spacing();
    ImGui::Spacing();

    if (ImGui::Button("Back to Engine"))
    {
        m_currentPage = Page::Engine;
    }
}

void GUI::DrawStatusBar()
{
    ImGuiViewport* viewport = ImGui::GetMainViewport();

    const float statusBarHeight = 28.0f;

    ImGui::SetNextWindowPos(
        ImVec2(
            viewport->Pos.x,
            viewport->Pos.y + viewport->Size.y - statusBarHeight
        )
    );

    ImGui::SetNextWindowSize(
        ImVec2(
            viewport->Size.x,
            statusBarHeight
        )
    );

    ImGuiWindowFlags flags =
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoCollapse;

    ImGui::Begin("Status Bar", nullptr, flags);

    ImGui::Text("Ready");

    ImGui::SameLine();

    ImGui::SetCursorPosX(
        ImGui::GetWindowWidth() - 150.0f
    );

    ImGui::Text("OpenPropulsion");

    ImGui::End();
}