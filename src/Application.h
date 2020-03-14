//
// Created by Emilien Lemaire on 09/12/2019.
//
/*
 * \file Application.h
 * \author Emilien Lemaire
 */
#pragma once

//TODO: App Init and enables;

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Window.h"

namespace ftn {
    //Classe statique qui contrôle la création et le réglage de l'application
    class Application {
    private:
        static std::shared_ptr<Window> s_Window;
        static Application* s_Instance;
        Application();
    public:
        ~Application();

        static void Init();

        static void Destroy();

        static void Enable(GLenum t_Cap);

        static Application* Get();

        /**
         * Set depth func and depth range
         * @param t_Func
         * @param t_ZNear
         * @param t_ZFar
         */
        static void SetDepthFunc(GLenum t_Function, GLfloat t_ZNear, GLfloat t_ZFar);
        static void SetBlendFunc(GLenum t_SFactor, GLenum t_DFactor);

        static void SetClearColor(GLfloat t_R, GLfloat t_G, GLfloat t_B, GLfloat t_A);

        /**
         * Set the window pointer and initialize glew
         * @param t_Window
         */
        static void InitGlew();
    };
}