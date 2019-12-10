//
// Created by Emilien Lemaire on 09/12/2019.
//

#include "Renderer.h"

namespace ftn {

    Renderer::Renderer(GLbitfield t_ClearMask)
            :m_ClearMask(t_ClearMask){}

    void Renderer::setClearMask(GLbitfield t_ClearMask) {
        m_ClearMask = t_ClearMask;
    }

    void Renderer::clear() const {
        glClear(m_ClearMask);
    }

    void Renderer::render(Shader& t_Shader) const {
        t_Shader.bind();

        t_Shader.addUniformMat4("u_Model", glm::mat4(1.f) * glm::translate(glm::mat4(1.f), glm::vec3(-500.f, -350.f, 0.f)));
        t_Shader.addUniformMat4("u_View", glm::lookAt(glm::vec3(0.0, .0, 800.f),
                                                      glm::vec3(0.0, 0.0, .1),
                                                      glm::vec3(0, 1., .0)));
        t_Shader.addUniformMat4("u_Projection", glm::perspective(45.f, 1000.f / 700.f, -10.f, 10.f));

        t_Shader.addUniform3f("u_LightPos", glm::vec3(0.0, .0, 800.f));
        t_Shader.addUniform3f("u_ViewPos", glm::vec3(0.0, .0, 800.f));
        t_Shader.addUniformMat4("u_FragModel", glm::mat4(1.f) * glm::translate(glm::mat4(1.f), glm::vec3(-500.f, -350.f, 0.f)));

        for (const Element& element: m_Elements) {
            glm::vec3 color = element.getColor();
            t_Shader.addUniform3f("u_Color", color);
            element.render();
        }

        t_Shader.unbind();
    }

    void Renderer::addElement(Element element) {
        m_Elements.push_back(element);
    }

    Renderer::~Renderer() = default;
}