//
// Created by Emilien Lemaire on 04/12/2019.
//

#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Log.h>

class Window {
private:
    GLFWwindow* m_Window = nullptr;
    GLuint m_Width;
    GLuint m_Height;
    const char* m_Title;
    bool m_EscToQuit = false;
public:
    Window(GLuint t_Width, GLuint t_Height, const char* t_Title);
    void setClearColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a) const;
    void enable(GLenum cap) const;
    void setDepthFunc(GLenum func, GLfloat zNear, GLfloat zFar) const;
    void setInputMode(int mode, int value) const;
    void setEscapeToQuit(bool value);
    void show();

    virtual ~Window();
};



