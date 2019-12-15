//
// Created by Emilien Lemaire on 09/12/2019.
//

#include "Application.h"

namespace ftn {
    Application* Application::s_Instance = nullptr;
    std::shared_ptr<Window> Application::s_Window = nullptr;

    Application::Application() = default;

    Application::~Application() {
        Log::Debug("Application Destroyed");
    }

    void Application::Init() {
        s_Instance = new Application();
        if (!glfwInit()) {
            Log::Fatal("Failed to initialize GLFW");
        }

        Log::Debug("GLFW Initialized");

        glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // On veut OpenGL 3.3
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,
                       GL_TRUE); // Pour rendre MacOS heureux ; ne devrait pas être nécessaire
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_DEPTH_BITS, 24);
    }

    void Application::Destroy() {
        if (s_Instance) {
            delete s_Instance;
            s_Instance = nullptr;
        }
        glfwTerminate();
    }

    void Application::Enable(GLenum t_Cap) {
        glEnable(t_Cap);
    }

    void Application::SetDepthFunc(GLenum t_Function, GLfloat t_ZNear, GLfloat t_ZFar) {
        glDepthMask(GL_TRUE);
        glDepthFunc(t_Function);
        glDepthRange(t_ZNear, t_ZFar);
    }

    void Application::SetWindow(const std::shared_ptr<Window> &t_Window) {
        s_Window = t_Window;

        glewExperimental = true;
        if (glewInit() != GLEW_OK) {
            Log::Fatal("Failed to initialize glew");
        }
        Log::Debug("glew initialized");

        std::stringstream sstr;

        sstr << "OpenGL Version: " << glGetString(GL_VERSION);

        Log::Info(sstr.str());
    }

    void Application::SetClearColor(GLfloat t_R, GLfloat t_G, GLfloat t_B, GLfloat t_A) {
        glClearColor(t_R, t_G, t_B, t_A);
    }

    Application* Application::Get() {
        return s_Instance;
    }
}