//
// Created by Emilien Lemaire on 09/12/2019.
//

#pragma once

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

#include "Element.h"
#include "Shader.h"
#include "Window.h"
#include "Camera.h"

namespace ftn {
    class Renderer {
    private:
        GLbitfield m_ClearMask;
        std::vector<Element> m_Elements;
        glm::vec3 m_LastColor = {1.f, 1.f, 1.f};
        std::unique_ptr<Camera> m_Camera;
        std::shared_ptr<Window> m_Window = nullptr;
        float m_LastTime = 0.f;
    public:
        explicit Renderer(GLbitfield t_ClearMask);

        void addElement(const Element& element);

        void setClearMask(GLbitfield t_ClearMask);

        void setTransform(int t_Index, bool t_Enable);

        void render(Shader& t_Shader);

        void clear() const;

        const std::shared_ptr<Window> &getWindow() const;

        void setWindow(const std::shared_ptr<Window> &t_Window);

        ~Renderer();
    };
}