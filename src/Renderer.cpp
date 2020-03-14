//
// Created by Emilien Lemaire on 09/12/2019.
//

#include <imgui.h>
#include <examples/imgui_impl_opengl3.h>
#include <examples/imgui_impl_glfw.h>
#include "Renderer.h"

namespace ftn {

    Renderer::Renderer(GLbitfield t_ClearMask)
            :m_ClearMask(t_ClearMask){
        m_Camera = std::make_unique<Camera>(glm::vec3(0.f, 0.f, 1000.f), 1000.f / 700.f);
    }

    void Renderer::setClearMask(GLbitfield t_ClearMask) {
        m_ClearMask = t_ClearMask;
    }

    void Renderer::clear() const {
        glClear(m_ClearMask);
    }

    float xPos = 0.f, yPos = 0.f, zPos = 1000.f;
    float angle = 0.f;
    glm::mat4 model(1.f);

    float win = 0.f;
    float lose = 0.f;

    void Renderer::render(Shader& t_Shader) {

        if (m_Window.get() == nullptr)
            Log::Fatal("42ngine Core", "You must set up a window for Renderer");

        float now = glfwGetTime();
        float timeStep = now - m_LastTime;
        m_LastTime = now;

        m_Camera->onUpdate(timeStep);

        t_Shader.bind();

        t_Shader.addUniformMat4("u_Model", model * glm::translate(model, glm::vec3(-500.f, -350.f, 0.f)));
        t_Shader.addUniformMat4("u_ViewProjection", m_Camera->getViewProjection());

        t_Shader.addUniform3f("u_LightPos", glm::vec3(0.0, .0, 1000.f));
        t_Shader.addUniform3f("u_ViewPos", glm::vec3(0.0, .0, 1000.f));
        t_Shader.addUniformMat4("u_FragModel", model * glm::translate(model, glm::vec3(-500.f, -350.f, 0.f)));


        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        {
            ImGui::Text("%.3f ms (FPS: %.1f)", timeStep, 1/timeStep);
        }

        for (int i = 0; i < m_Elements.size(); i++) {
            Element element = m_Elements[i];
            glm::vec3 color = element.getColor();


            if (element.getTransform().enabled){
                t_Shader.addUniformMat4("u_Transform", element.getTransform().transform);
                t_Shader.addUniform3f("u_Color", glm::vec3(.8f,0.2f,0.5f));
            } else {
                t_Shader.addUniformMat4("u_Transform", glm::mat4(1.f));
                t_Shader.addUniform3f("u_Color", color);
            }

            if(i == 0){
                t_Shader.addUniform1f("u_Win", win);
            } else {
                t_Shader.addUniform1f("u_Win", lose);
            }

            m_LastColor = color;
            element.render();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        t_Shader.unbind();
    }

    void Renderer::addElement(const Element& element) {
        m_Elements.push_back(element);
    }

    const std::shared_ptr<Window> &Renderer::getWindow() const {
        return m_Window;
    }

    void Renderer::setWindow(const std::shared_ptr<Window> &t_Window) {
        m_Camera->setWindow(t_Window);
        m_Window = t_Window;
    }

    void Renderer::setTransform(int t_Index, bool t_Enable) {
        m_Elements[t_Index].enableTransform(t_Enable);
    }

    Renderer::~Renderer() = default;
}