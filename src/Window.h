//
// Created by Emilien Lemaire on 04/12/2019.
//

#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Log.h>
#include "Shader.h"
#include "VertexArray.h"

namespace ftn {
    class Window {
    private:
        GLFWwindow *m_Window = nullptr;
        GLuint m_Width;
        GLuint m_Height;
        const char *m_Title;
        bool m_EscToQuit = false;
    public:
        Window(GLuint t_Width, GLuint t_Height, const char *t_Title);

        void setInputMode(int t_Mode, int t_Value) const;

        void setEscapeToQuit(bool t_Value);

        void update() const;

        bool shouldClose() const;

        GLFWwindow* getWindow() const { return m_Window; }

        virtual ~Window();
    };
}