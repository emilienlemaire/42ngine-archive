//
// Created by Emilien Lemaire on 12/12/2019.
//

#include "CameraController.h"
namespace ftn {

    CameraController::CameraController(float t_AspectRatio, glm::vec3 t_CameraPosition)
            :m_AspectRatio(t_AspectRatio),
             m_Camera(std::make_unique<Camera>(t_CameraPosition, t_AspectRatio)),
             m_CameraPosition(t_CameraPosition),
             m_CameraDirection({0.f, 0.f, 0.f})
    {}

    CameraController::~CameraController() = default;



    void CameraController::onKeyPressed(int t_KeyCode, int t_Action) {


        if(t_Action == GLFW_PRESS || t_Action == GLFW_REPEAT) {
            switch (t_KeyCode) {
                case GLFW_KEY_W:
                    m_CameraPosition += m_CameraDirection * m_TranslationSpeed * m_TimeStep;
                    break;
                case GLFW_KEY_A:
                    m_CameraPosition += m_CameraLeft * m_TranslationSpeed * m_TimeStep;
                    break;
                case GLFW_KEY_S:
                    m_CameraPosition -= m_CameraDirection * m_TranslationSpeed * m_TimeStep;
                    break;
                case GLFW_KEY_D:
                    m_CameraPosition -= m_CameraLeft * m_TranslationSpeed * m_TimeStep;
                    break;
                default:
                    break;
            }
            m_CameraTarget = m_CameraPosition + m_CameraDirection;
            m_Camera->setTarget(m_CameraTarget);
            m_Camera->setPosition(m_CameraPosition);
        }
    }

    void CameraController::onMouseMotion(float xPos, float yPos) {
        m_Theta -= xPos * m_MouseSensitivity;
        m_Phi -= yPos * m_MouseSensitivity;
        updateVectors();
    }

    void CameraController::updateVectors() {
        static const glm::vec3 up(0.f, 0.f, 1.f);

        if(m_Phi > 89.f)
            m_Phi = 89.f;
        else if (m_Phi < -89.f)
            m_Phi = -89.f;

        float rPhi = glm::radians(m_Phi);
        float rTheta = glm::radians(m_Theta);

        m_CameraDirection.x = glm::cos(rPhi) * glm::cos(rTheta);
        m_CameraDirection.y = glm::cos(rPhi) * glm::sin(rTheta);
        m_CameraDirection.z = glm::sin(rPhi);

        m_CameraLeft = glm::cross(up, m_CameraDirection);
        glm::normalize(m_CameraLeft);

        m_CameraTarget = m_CameraPosition * m_CameraDirection;
        m_Camera->setTarget(m_CameraTarget);
    }

    void CameraController::onUpdate(float t_TimeStep) {
        m_TimeStep = t_TimeStep;
        m_Camera->setPosition(m_CameraPosition);
        m_Camera->setTarget(m_CameraTarget);
    }

    const std::unique_ptr<Camera> &CameraController::getCamera() const {
        return m_Camera;
    }
}