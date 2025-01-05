#pragma once

#include <glm/glm.hpp>

namespace roo
{
    class Camera
    {
    public:
        Camera(float left, float right, float bottom, float top);
        ~Camera() = default;

        const glm::vec3& GetPosition() const;
        void SetPosition(const glm::vec3& position);


        // Returns rotation in degrees
        float GetRotation() const;

        // Sets rotation in degrees
        void SetRotation(float rotation);


        const glm::mat4& GetProjectionMatrix() const;
        const glm::mat4& GetViewMatrix() const;
        const glm::mat4& GetViewProjectionMatrix() const;

    private:
        void RecalculateViewMatrix();

        glm::mat4 m_ProjectionMatrix;
        glm::mat4 m_ViewMatrix;
        glm::mat4 m_ViewProjectionMatrix;

        glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
        float m_Rotation = 0.0f;
    };
}