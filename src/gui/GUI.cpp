#include "GUI.h"

#include "iostream"
#include "imgui.h"
#include "imgui_internal.h"
#include "implot.h"

#include <vector>

GUI::GUI(Simulation& simulation) : m_simulation(simulation)
{
    ImGuiIO& io = ImGui::GetIO();

    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    m_interRegular = io.Fonts->AddFontFromFileTTF(
        "assets/fonts/Inter_18pt-Regular.ttf",
        16.0f
    );

    m_interMedium = io.Fonts->AddFontFromFileTTF(
        "assets/fonts/Inter_18pt-Medium.ttf",
        16.0f
    );

    m_interSemiBold = io.Fonts->AddFontFromFileTTF(
        "assets/fonts/Inter_18pt-SemiBold.ttf",
        16.0f
    );

    io.FontDefault = m_interRegular;
}

GUI::~GUI()
{
    ImPlot::DestroyContext();
    ImGui::DestroyContext();
}

void GUI::Draw()
{
    DrawMenuBar();

    ImGuiID dockspace_id = ImGui::GetID("OpenPropulsionDockSpace");

    ImGui::DockSpaceOverViewport(
        dockspace_id,
        nullptr,
        ImGuiDockNodeFlags_PassthruCentralNode
    );

    static bool firstTime = true;

    if (firstTime)
    {
        firstTime = false;

        ImGui::DockBuilderRemoveNode(dockspace_id);

        ImGui::DockBuilderAddNode(
            dockspace_id,
            ImGuiDockNodeFlags_DockSpace
        );

        ImGui::DockBuilderSetNodeSize(
            dockspace_id,
            ImGui::GetMainViewport()->WorkSize
        );

        ImGuiID left;
        ImGuiID centre;
        ImGuiID right;
        ImGuiID centreTop;
        ImGuiID centreBottom;

        // Split off the left sidebar
        ImGui::DockBuilderSplitNode(
            dockspace_id,
            ImGuiDir_Left,
            0.20f,
            &left,
            &centre
        );

        // Split off the right analysis panel
        ImGui::DockBuilderSplitNode(
            centre,
            ImGuiDir_Right,
            0.20f,
            &right,
            &centre
        );

        // Split the centre into viewport and results
        ImGui::DockBuilderSplitNode(
            centre,
            ImGuiDir_Down,
            0.48f,
            &centreBottom,
            &centreTop
        );

        ImGui::DockBuilderGetNode(left)->LocalFlags |= ImGuiDockNodeFlags_NoTabBar;
        ImGui::DockBuilderGetNode(centreTop)->LocalFlags |= ImGuiDockNodeFlags_NoTabBar;
        ImGui::DockBuilderGetNode(centreBottom)->LocalFlags |= ImGuiDockNodeFlags_NoTabBar;
        ImGui::DockBuilderGetNode(right)->LocalFlags |= ImGuiDockNodeFlags_NoTabBar;

        // Dock each window into its node
        ImGui::DockBuilderDockWindow("Sidebar", left);
        ImGui::DockBuilderDockWindow("Viewport", centreTop);
        ImGui::DockBuilderDockWindow("Results", right);
        ImGui::DockBuilderDockWindow("Analysis", centreBottom);

        ImGui::DockBuilderFinish(dockspace_id);
    }

    DrawSidebar();
    DrawViewport();
    DrawResults();
    DrawAnalysis();
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
    ImGui::Begin(
        "Sidebar",
        nullptr,
        ImGuiWindowFlags_NoCollapse
    );

    ImGui::InputInt("Altitude", &m_simulation.altitude, 100, 10000);    
    ImGui::InputFloat("Mach", &m_simulation.mach, 0.0, 5.0); 
    ImGui::SliderInt("Throttle", &m_simulation.throttle, 0, 100);

    if (ImGui::Button("Run Simulation", ImVec2(-1, 0)))
    {
        m_simulation.Run();
        RunThrustAnalysis();
    }

    ImGui::End();
}

void GUI::DrawViewport()
{
    ImGui::Begin(
        "Viewport",
        nullptr,
        ImGuiWindowFlags_NoCollapse
    );

    // Draw your viewport content here

    ImGui::End();
}

void GUI::DrawResults()
{
    ImGui::Begin(
        "Results",
        nullptr,
        ImGuiWindowFlags_NoCollapse
    );

    // Draw your results content here

    ImGui::Text("Thrust: %.2f N", m_simulation.thrust);
    ImGui::Text("Net Thrust: %.2f N", m_simulation.netThrust);
    ImGui::Text("TSFC: %.10f kg/N/s", m_simulation.tsfc);
    ImGui::Text("Fuel Flow: %.2f kg/s", m_simulation.fuelFlow);
    ImGui::Text("Specific Impulse: %.2f s", m_simulation.specificImpulse);
    ImGui::Text("Exit Velocity: %.2f m/s", m_simulation.exitVelocity);
    ImGui::Text("Exit Pressure: %.2f kPa", m_simulation.exitPressure);
    ImGui::Text("Exit Temperature: %.2f K", m_simulation.exitTemperature);
    ImGui::Text("Exit Mach: %.2f", m_simulation.exitMach);
    ImGui::Text("Mass Flow: %.2f kg/s", m_simulation.massFlow);
    ImGui::Text("Density: %.2f kg/m³", m_simulation.density);
    ImGui::Text("Speed of Sound: %.2f m/s", m_simulation.speedOfSound);

    ImGui::End();
}

void GUI::DrawAnalysis()
{
    ImGui::SetNextWindowSize(ImVec2(400, 600), ImGuiCond_FirstUseEver);
    ImGui::Begin(
        "Analysis",
        nullptr,
        ImGuiWindowFlags_NoCollapse
    );

    if (ImGui::BeginTabBar("AnalysisTabs"))
    {
        if (ImGui::BeginTabItem("Thrust Analysis"))
        {
            DrawThrustAnalysis();
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Other Analysis"))
        {
            // Draw other analysis content here
            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
    }

    ImGui::End();
}

void GUI::RunThrustAnalysis()
{
    m_altitudes.clear();
    m_thrusts.clear();

    for (int altitude = 0; altitude <= 20000; altitude += 1000)
    {
        Simulation simulation(
            altitude,
            m_simulation.mach,
            m_simulation.throttle
        );

        simulation.Run();

        m_altitudes.push_back(static_cast<float>(altitude));
        m_thrusts.push_back(simulation.thrust);
    }
}
void GUI::DrawThrustAnalysis()
{
    if (ImPlot::BeginPlot("Thrust vs Altitude", ImVec2(-1, -1)))
    {
        ImPlot::SetupAxes(
            "Altitude (m)",
            "Thrust (N)"
        );

        if (!m_altitudes.empty())
        {
            ImPlot::PlotLine(
                "Thrust",
                m_altitudes.data(),
                m_thrusts.data(),
                static_cast<int>(m_altitudes.size())
            );
        }

        ImPlot::EndPlot();
    }
}