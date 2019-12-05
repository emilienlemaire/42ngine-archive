//
// Created by Emilien Lemaire on 04/12/2019.
//

#include <sstream>
#include <glm/gtx/transform.hpp>
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

void Window::show(const Shader& shader, const VertexArray& va) {
    Log::Info("Window opened");
    do{
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.bind();


        glm::mat4 projection = glm::perspective(45.f, 1000.f/700.f, -10.f, 10.f);
        glm::mat4 m_View = glm::lookAt(
                glm::vec3(0.0, .0, 1000.f),
                glm::vec3(0.0, 0.0, .1),
                glm::vec3(0, 1., .0)
                );
        glm::mat4 m_Model = glm::mat4(1.f);
        glm::mat4 m_Translation = glm::translate(glm::vec3(-500.f, -350.f, .0f));
        glm::mat4 m_MVP = projection * m_View * m_Model * m_Translation;

        glm::mat4 u_Model = m_Model * m_Translation;

        shader.addUniformMat4("u_MVP", m_MVP);
        shader.addUniformMat4("u_Model", u_Model);
        shader.addUniformMat4("u_FragModel", u_Model);
        shader.addUniformMat4("u_View", m_View);
        for (int i = 0; i < va.getMNumberOfVao(); ++i) {
            va.bind(i);
            while (glGetError());
            glDrawArrays(GL_TRIANGLES, 0, va.getMDrawSize()[i] / 3);
            GLenum error = glGetError();
            if(error)
                Log::Error(std::to_string(error));
        }
        glfwSwapBuffers(m_Window);
        glfwPollEvents();
    } while(m_EscToQuit ?( !glfwWindowShouldClose(m_Window) && glfwGetKey(m_Window, GLFW_KEY_ESCAPE) != GLFW_PRESS) : !glfwWindowShouldClose(m_Window));

    Log::Info("Window closed");
}

Window::~Window() {
    glfwDestroyWindow(m_Window);
}

void Window::setClearColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a) const {
    glClearColor(r, g, b, a);
}

void Window::enable(GLenum cap) const {
    glEnable(cap);
}

void Window::setDepthFunc(GLenum func, GLfloat zNear, GLfloat zFar) const{
    glDepthFunc(func);
    glDepthRange(zNear, zFar);
}

void Window::setInputMode(int mode, int value) const {
    glfwSetInputMode(m_Window, mode, value);
}

void Window::setEscapeToQuit(bool value) {
    m_EscToQuit  = value;
}
