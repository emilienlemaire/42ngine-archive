//
// Created by Emilien Lemaire on 04/12/2019.
//

#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <CppLogger/Log.h>

class Window {
private:
    GLFWwindow* m_Window = nullptr;
    GLuint m_Width;
    GLuint m_Height;
    const char* m_Title;
public:
    Window(GLuint t_Width, GLuint t_Height, const char* t_Title);
    void show();

    virtual ~Window();
};



