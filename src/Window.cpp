//
// Created by Emilien Lemaire on 04/12/2019.
//

#include <sstream>
#include "Window.h"

Window::Window(GLuint t_Width, GLuint t_Height, const char* t_Title)
    :m_Width(t_Width), m_Height(t_Height), m_Title(t_Title)
{
    if (!glfwInit()){
        Log::Fatal("Failed to initialize GLFW");
    }

    Log::Debug("GLFW Initialized");

    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // On veut OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Pour rendre MacOS heureux ; ne devrait pas être nécessaire
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_DEPTH_BITS, 24);

    m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, nullptr, nullptr);

    if (!m_Window){
        Log::Fatal("GLFW failed to create the window");
    }

    Log::Debug("Window created");

    glfwMakeContextCurrent(m_Window);

    glewExperimental = true;
    if (glewInit() != GLEW_OK){
        Log::Fatal("Failed to initialize glew");
    }
    Log::Debug("glew initialized");

    std::stringstream sstr;

    sstr << "OpenGL Version: " << glGetString(GL_VERSION);

    Log::Info(sstr.str());
}

void Window::show() {
    Log::Info("Window opened");
    do{
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glfwSwapBuffers(m_Window);
        glfwPollEvents();
    } while(!glfwWindowShouldClose(m_Window));

    Log::Info("Window closed");
}

Window::~Window() {
    glfwDestroyWindow(m_Window);
}
