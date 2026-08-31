#include "Application.h"

#include "../gui/GUI.h"

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include <GLFW/glfw3.h>

Application::Application()
{
}

Application::~Application()
{
    Shutdown();
}

int Application::Run()
{
    if (!Initialize())
        return 1;

    while (!glfwWindowShouldClose(m_window))
    {
        BeginFrame();

        m_gui->Draw();

        EndFrame();
    }

    return 0;
}

bool Application::Initialize()
{
    // --------------------------------------------------------
    // GLFW
    // --------------------------------------------------------

    if (!glfwInit())
        return false;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(
        1280,
        720,
        "OpenPropulsion",
        nullptr,
        nullptr
    );

    if (!m_window)
    {
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1);

    // --------------------------------------------------------
    // Dear ImGui
    // --------------------------------------------------------

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    (void)io;

    ImGui::StyleColorsLight();

    // --------------------------------------------------------
    // ImGui backends
    // --------------------------------------------------------

    if (!ImGui_ImplGlfw_InitForOpenGL(m_window, true))
        return false;

    if (!ImGui_ImplOpenGL3_Init("#version 330"))
        return false;

    // --------------------------------------------------------
    // GUI
    // --------------------------------------------------------

    m_gui = new GUI(m_simulation);

    return true;
}

void Application::BeginFrame()
{
    glfwPollEvents();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();

    ImGui::NewFrame();
}

void Application::EndFrame()
{
    ImGui::Render();

    int displayWidth;
    int displayHeight;

    glfwGetFramebufferSize(
        m_window,
        &displayWidth,
        &displayHeight
    );

    glViewport(
        0,
        0,
        displayWidth,
        displayHeight
    );

    glClearColor(
        0.95f,
        0.95f,
        0.95f,
        1.0f
    );

    glClear(GL_COLOR_BUFFER_BIT);

    ImGui_ImplOpenGL3_RenderDrawData(
        ImGui::GetDrawData()
    );

    glfwSwapBuffers(m_window);
}

void Application::Shutdown()
{
    if (m_gui)
    {
        delete m_gui;
        m_gui = nullptr;
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();

    if (ImGui::GetCurrentContext())
        ImGui::DestroyContext();

    if (m_window)
    {
        glfwDestroyWindow(m_window);
        m_window = nullptr;
    }

    glfwTerminate();
}