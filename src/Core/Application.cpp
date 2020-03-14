//
// Created by Emilien Lemaire on 09/12/2019.
//

#include "Application.h"

namespace ftn {
    std::shared_ptr<Window> Application::s_Window = nullptr;

    Application::Application() = default;

    Application::~Application() {
        Log::Debug("42ngine Core", "Application Destroyed");
    }

    void Application::Init() {
        Log::createConsole("42ngine Core", Log::LevelDebug);
        //On initialise le pointeur static de l'application et GLFW. Si GLFW est aml initialisé on arrête le programme
        if (!glfwInit()) {
            Log::Fatal("42ngine Core", "Failed to initialize GLFW");
        }

        Log::Debug("42ngine Core", "GLFW Initialized");

        //On définie différents paramètres pour notre application.
        glfwWindowHint(GLFW_SAMPLES, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_DEPTH_BITS, 24);
    }

    void Application::Enable(GLenum t_Cap) {
        glEnable(t_Cap);
    }

    void Application::SetDepthFunc(GLenum t_Function, GLfloat t_ZNear, GLfloat t_ZFar) {
        glDepthMask(GL_TRUE);
        glDepthFunc(t_Function);
        glDepthRange(t_ZNear, t_ZFar);
    }

    void Application::InitGlew() {
        //Afin que glew s'initialise il faut une fenêtre j'ai donc fait une fonction différente
        // qui est appelée plus tard dans main.

        glewExperimental = true;

        //Si glew est mal initialisé on stop l'application.
        if (glewInit() != GLEW_OK) {
            Log::Fatal("42ngine Core", "Failed to initialize glew");
        }
        Log::Debug("42ngine Core", "glew initialized");

        std::stringstream sstr;

        sstr << "OpenGL Version: " << glGetString(GL_VERSION);

        Log::Info("42ngine Core", sstr.str());
    }

    void Application::SetClearColor(GLfloat t_R, GLfloat t_G, GLfloat t_B, GLfloat t_A) {
        glClearColor(t_R, t_G, t_B, t_A);
    }

    void Application::SetBlendFunc(GLenum t_SFactor, GLenum t_DFactor) {
        glBlendFunc(t_SFactor, t_DFactor);
    }

    void Application::run() {
        while(true);
    }
}