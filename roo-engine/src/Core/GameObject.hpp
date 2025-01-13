#pragma once

#include <glm/glm.hpp>

namespace roo
{
    class GameObject
    {
    public:
        GameObject();
        virtual ~GameObject();

        virtual void Draw() = 0;

        glm::vec2 GetPosition();
        glm::vec2 GetSize();
        float GetRotation();
        bool GetVisible();

        void SetPosition(glm::vec2 position);
        void SetSize(glm::vec2 size);
        void SetRotation(float angle);
        void SetVisible(bool visible);

    protected:
        glm::mat4 m_Transform;

        glm::vec3 m_Position;
        glm::vec3 m_Size;
        float m_Rotation;

        bool m_Visible;

    private:
        void CalculateTransformMatrix();
    };
}