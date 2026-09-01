#include "GUI.h"

#include "iostream"
#include "imgui.h"
#include "imgui_internal.h"

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
            0.30f,
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
        ImGui::DockBuilderDockWindow("Results", centreBottom);
        ImGui::DockBuilderDockWindow("Analysis", right);

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

    ImGui::End();
}

void GUI::DrawAnalysis()
{
    ImGui::Begin(
        "Analysis",
        nullptr,
        ImGuiWindowFlags_NoCollapse
    );

    // Draw your analysis content here

    ImGui::End();
}