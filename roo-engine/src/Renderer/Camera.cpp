#include "Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace roo
{
    Camera::Camera(float left, float right, float bottom, float top)
        : m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)),
        m_ViewMatrix(1.0f),
        m_Position({ 0.0f, 0.0f, 0.0f }),
        m_Rotation(0.0f)
    {
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    const glm::vec3& Camera::GetPosition() const
    {
        return m_Position;
    }

    void Camera::SetPosition(const glm::vec3& position)
    {
        m_Position = position;
        RecalculateViewMatrix();
    }

    float Camera::GetRotation() const
    {
        return m_Rotation;
    }

    void Camera::SetRotation(float rotation)
    {
        m_Rotation = rotation;
        RecalculateViewMatrix();
    }

    const glm::mat4& Camera::GetProjectionMatrix() const
    {
        return m_ProjectionMatrix;
    }

    const glm::mat4& Camera::GetViewMatrix() const
    {
        return m_ViewMatrix;
    }

    const glm::mat4& Camera::GetViewProjectionMatrix() const
    {
        return m_ViewProjectionMatrix;
    }

    void Camera::RecalculateViewMatrix()
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *
            glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));

        m_ViewMatrix = glm::inverse(transform);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }
}