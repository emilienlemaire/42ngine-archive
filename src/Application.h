//
// Created by Emilien Lemaire on 09/12/2019.
//

#pragma once

//TODO: App init and enables;

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Window.h"

namespace ftn {
    class Application {
    private:
        Window* m_Window = nullptr;
    public:
        Application();
        ~Application();

        void init();
        void destroy();
        void enable(GLenum t_Cap) const;
        void setDepthFunc(GLenum t_Func, GLfloat t_ZNear, GLfloat t_ZFar) const;
        void setClearColor(GLfloat t_R, GLfloat t_G, GLfloat t_B, GLfloat t_A) const;
        void setWindow(Window* t_Window);
    };
}