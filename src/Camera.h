//
// Created by Emilien Lemaire on 12/12/2019.
//

#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Window.h"

namespace ftn {
    class Camera {
    private:
        glm::vec3 m_Position;
        glm::vec3 m_Target = glm::vec3(0.f);
        glm::vec3 m_Up = glm::vec3(0.f, 1.f, 0.f);
        glm::vec3 m_Direction = glm::vec3(0.f, 0.f, -1.f);
        glm::vec3 m_Left = glm::vec3(-1.f, 0.f, 0.f);

        glm::mat4 m_Projection;
        glm::mat4 m_View;
        glm::mat4 m_ViewProjection;

        float m_TranslationSpeed = 500.f;
        float m_MouseSensibility = .1f;
        float m_Theta = 90.f;
        float m_Phi = 0.f;

        float m_LastX;
        float m_LastY;

        std::shared_ptr<Window> m_Window = nullptr;
    public:
        Camera(glm::vec3 t_Position, float t_AspectRation);
        ~Camera();

        const glm::vec3 &getPosition() const;

        void setPosition(const glm::vec3 &t_Position);

        const glm::vec3 &getTarget() const;

        void setTarget(const glm::vec3 &t_Target);

        const glm::vec3 &getUp() const;

        void setUp(const glm::vec3 &t_Up);

        const glm::mat4 &getProjection() const;

        const glm::mat4 &getView() const;

        const glm::mat4 &getViewProjection() const;

        void setWindow(const std::shared_ptr<Window> &t_Window);

        const std::shared_ptr<Window> &getWindow() const;

        void onUpdate(float t_TimeStep);

    private:
        void recalculateMatrices();
    };
}



