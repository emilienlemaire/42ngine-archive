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

        //Si la fen^^re ne se crée pas on stop le programme.
        if (!m_Window) {
            Log::Fatal("42ngine Core", "GLFW failed to create the window");
        }

        Log::Debug("42ngine Core", "Window created");

        //On lie la fenêtre à GLFW
        glfwMakeContextCurrent(m_Window);

        //Initlisation de ImGUI.
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
        if(t_Mode == GLFW_RAW_MOUSE_MOTION)
            glfwSetCursorPos(m_Window, 500.f, 350.f);
    }

    void Window::setEscapeToQuit(bool t_Value) {
        //Si l'utilisateur veut pouvoir quitter le programme avec la touche escape on lui en donne l'opportunité.
        m_EscToQuit = t_Value;
    }

    void Window::update(){
        glfwSwapBuffers(m_Window);
        glfwPollEvents();
    }

    bool Window::shouldClose() const{
        //Si l'utilisateur veut pouvoir quitter le programme avec la touche escape on lui en donne l'opportunité.
        bool esc = false;
        if (m_EscToQuit){
            esc = glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS;
        }

        return glfwWindowShouldClose(m_Window) || esc;
    }

    void Window::setVSync(bool t_Enable) {
        m_VSync = t_Enable;
        if (m_VSync)
            //On lie le rafraîchissement de l'application à celui de l'écran afin d'éviter des calcul inutile et
            // pour de meilleurs performances.
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);
    }
}