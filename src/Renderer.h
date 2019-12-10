//
// Created by Emilien Lemaire on 09/12/2019.
//

#pragma once

#include <GL/glew.h>
#include <glm/gtx/transform.hpp>

#include "Element.h"
#include "Shader.h"

namespace ftn {
    class Renderer {
    private:
        GLbitfield m_ClearMask;
        std::vector<Element> m_Elements;
    public:
        Renderer(GLbitfield t_ClearMask);

        void addElement(Element element);

        void setClearMask(GLbitfield t_ClearMask);

        void render(Shader& t_Shader) const;

        void clear() const;

        ~Renderer();
    };
}