//
// Created by Emilien Lemaire on 04/12/2019.
//

#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <CppLogger/src/Log.h>

namespace ftn {
    class Window {
    private:
        GLFWwindow *m_Window = nullptr;
        GLuint m_Width;
        GLuint m_Height;

        float m_LastTime = 0.f;

        const char *m_Title;
        bool m_EscToQuit = false;
        bool m_VSync = false;
    public:
        Window(GLuint t_Width, GLuint t_Height, const char *t_Title);

        void setInputMode(int t_Mode, int t_Value) const;

        void setEscapeToQuit(bool t_Value);

        void update();

        bool shouldClose() const;

        GLFWwindow* getWindow() const { return m_Window; }

        void setVSync(bool t_Enable);

        virtual ~Window();
    };
}