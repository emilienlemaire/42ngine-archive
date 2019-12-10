//
// Created by Emilien Lemaire on 04/12/2019.
//
#include <imgui.h>
#include <examples/imgui_impl_glfw.h>
#include <examples/imgui_impl_opengl3.h>
#include "Window.h"

namespace ftn {
    Window::Window(GLuint t_Width, GLuint t_Height, const char *t_Title)
            : m_Width(t_Width), m_Height(t_Height), m_Title(t_Title) {

        m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, nullptr, nullptr);

        if (!m_Window) {
            Log::Fatal("GLFW failed to create the window");
        }

        Log::Debug("Window created");

        glfwMakeContextCurrent(m_Window);

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        ImGuiIO& io = ImGui::GetIO();
        (void)io;

        ImGui::StyleColorsDark();

        ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
        ImGui_ImplOpenGL3_Init("#version 330 core");
    }

    Window::~Window() {
        glfwDestroyWindow(m_Window);
    }

    void Window::setInputMode(int t_Mode, int t_Value) const {
        glfwSetInputMode(m_Window, t_Mode, t_Value);
    }

    void Window::setEscapeToQuit(bool t_Value) {
        m_EscToQuit = t_Value;
    }

    void Window::update(GLfloat* angle) const{

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        {
            ImGui::Begin("Test");
            ImGui::SliderFloat("Angle", angle, 0.f, 360.f);
            ImGui::End();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(m_Window);
        glfwPollEvents();
    }

    bool Window::shouldClose() const{
        bool esc = false;
        if (m_EscToQuit){
            esc = glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS;
        }

        return glfwWindowShouldClose(m_Window) || esc;
    }

    void Window::setVSync(bool t_Enable) {
        m_VSync = t_Enable;
        if (m_VSync)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);
    }
}