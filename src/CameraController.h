//
// Created by Emilien Lemaire on 12/12/2019.
//

#pragma once

#include "Camera.h"

namespace ftn {

    class CameraController {
    private:
        float m_AspectRatio;
        float m_TranslationSpeed = 5.f, m_MouseSensitivity = 1.f;
        float m_Theta = 0.f;
        float m_Phi = 0.f;
        float m_TimeStep = 0.f;

        glm::vec3 m_CameraPosition;
        glm::vec3 m_CameraDirection{};
        glm::vec3 m_CameraLeft = glm::vec3(0.f);
        glm::vec3 m_CameraTarget = glm::vec3(0.f);

        std::unique_ptr<Camera> m_Camera;

    public:
        explicit CameraController(float t_AspectRatio, glm::vec3 t_CameraPosition = {0.f, 0.f, 1000.f});
        ~CameraController();

        void onUpdate(float t_TimeStep);

        void onKeyPressed(int t_KeyCode, int t_Action);

        void onMouseMotion(float xPos, float yPos);

        const std::unique_ptr<Camera> &getCamera() const;

    private:
        void updateVectors();
    };


}




