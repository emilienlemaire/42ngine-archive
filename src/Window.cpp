//
// Created by Emilien Lemaire on 04/12/2019.
//
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

    void Window::update() const{
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
}