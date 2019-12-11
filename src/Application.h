//
// Created by Emilien Lemaire on 09/12/2019.
//
/*
 * \file Application.h
 * \author Emilien Lemaire
 */
#pragma once

//TODO: App init and enables;

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Window.h"

namespace ftn {
    class Application {
    private:
        std::shared_ptr<Window> m_Window;
    public:
        Application();
        ~Application();

        void init();

        void destroy();

        void enable(GLenum t_Cap) const;

        /**
         * Set depth func and depth range
         * @param t_Func
         * @param t_ZNear
         * @param t_ZFar
         */
        void setDepthFunc(GLenum t_Function, GLfloat t_ZNear, GLfloat t_ZFar) const;

        void setClearColor(GLfloat t_R, GLfloat t_G, GLfloat t_B, GLfloat t_A) const;

        /**
         * Set the window pointer and initialize glew
         * @param t_Window
         */
        void setWindow(const std::shared_ptr<Window> &t_Window);
    };
}