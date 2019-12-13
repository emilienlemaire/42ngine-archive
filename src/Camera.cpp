//
// Created by Emilien Lemaire on 12/12/2019.
//

#include "Camera.h"
namespace ftn {
    Camera::Camera(glm::vec3 t_Position, float t_AspectRation)
            :m_Position(t_Position),
             m_Projection(glm::perspective(glm::radians(45.f), t_AspectRation, .1f, 2000.f)),
             m_View(glm::lookAt(m_Position, m_Target, m_Up)),
             m_ViewProjection(m_Projection * m_View)
    {}

    const glm::vec3 &Camera::getPosition() const {
        return m_Position;
    }

    void Camera::setPosition(const glm::vec3 &t_Position) {
        m_Position = t_Position;
        recalculateMatrices();
    }

    const glm::vec3 &Camera::getTarget() const {
        return m_Target;
    }

    void Camera::setTarget(const glm::vec3 &t_Target) {
        m_Target = t_Target;
        recalculateMatrices();
    }

    const glm::vec3 &Camera::getUp() const {
        return m_Up;
    }

    void Camera::setUp(const glm::vec3 &t_Up) {
        m_Up = t_Up;
        recalculateMatrices();
    }

    void Camera::recalculateMatrices() {
        m_View = glm::lookAt(m_Position,m_Target, m_Up);
        m_ViewProjection = m_Projection * m_View;
    }

    const glm::mat4 &Camera::getProjection() const {
        return m_Projection;
    }

    const glm::mat4 &Camera::getView() const {
        return m_View;
    }

    const glm::mat4 &Camera::getViewProjection() const {
        return m_ViewProjection;
    }

    void Camera::onUpdate(float t_TimeStep) {

        if(glfwGetKey(m_Window->getWindow(), GLFW_KEY_W) == GLFW_PRESS
           || glfwGetKey(m_Window->getWindow(), GLFW_KEY_W) == GLFW_REPEAT){
            m_Position += m_Direction * m_TranslationSpeed * t_TimeStep;
        }

        if(glfwGetKey(m_Window->getWindow(), GLFW_KEY_S) == GLFW_PRESS
           || glfwGetKey(m_Window->getWindow(), GLFW_KEY_S) == GLFW_REPEAT){
            m_Position -= m_Direction * m_TranslationSpeed * t_TimeStep;
        }

        if(glfwGetKey(m_Window->getWindow(), GLFW_KEY_A) == GLFW_PRESS
           || glfwGetKey(m_Window->getWindow(), GLFW_KEY_A) == GLFW_REPEAT){
            m_Position += m_Left * m_TranslationSpeed * t_TimeStep;
        }

        if(glfwGetKey(m_Window->getWindow(), GLFW_KEY_D) == GLFW_PRESS
           || glfwGetKey(m_Window->getWindow(), GLFW_KEY_D) == GLFW_REPEAT){
            m_Position -= m_Left * m_TranslationSpeed * t_TimeStep;
        }

        double xPos, yPos;

        glfwGetCursorPos(m_Window->getWindow(), &xPos, &yPos);

        float xDiff = m_LastX - (float)xPos;
        float yDiff = m_LastY - (float)yPos;

        m_LastX = (float)xPos;
        m_LastY = (float)yPos;

        m_Theta -= (float)xDiff * m_MouseSensibility;
        m_Phi -= (float)yDiff * m_MouseSensibility;

        if (m_Phi > 89.f)
            m_Phi = 89.f;
        if (m_Phi < -89.f)
            m_Phi = -89.f;

        float rPhi = glm::radians(m_Phi);
        float rTheta = glm::radians(m_Theta);

        m_Direction.x = -glm::cos(rPhi) * glm::cos(rTheta);
        m_Direction.y = -glm::sin(rPhi);
        m_Direction.z = -glm::cos(rPhi) * glm::sin(rTheta);

        m_Left = glm::cross(m_Up, m_Direction);
        glm::normalize(m_Left);


        m_Target = m_Position + m_Direction;

        recalculateMatrices();
    }

    void Camera::setWindow(const std::shared_ptr<Window> &t_Window) {
        double x, y;
        glfwGetCursorPos(t_Window->getWindow(), &x, &y);

        m_LastX = (float)x;
        m_LastY = (float)y;

        m_Window = t_Window;
    }

    const std::shared_ptr<Window> &Camera::getWindow() const {
        return m_Window;
    }

    Camera::~Camera() = default;



}
