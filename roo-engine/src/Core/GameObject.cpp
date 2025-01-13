#include "GameObject.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace roo
{
    GameObject::GameObject()
        : m_Transform(1.0f),
        m_Position({ 0.0f, 0.0f, 0.0f}),
        m_Size({ 1.0f, 1.0f, 1.0f}),
        m_Rotation(0.0f),
        m_Visible(true)
    {
        CalculateTransformMatrix();
    }

    GameObject::~GameObject()
    {
    }

    glm::vec2 GameObject::GetPosition()
    {
        return m_Position;
    }

    glm::vec2 GameObject::GetSize()
    {
        return m_Size;
    }

    float GameObject::GetRotation()
    {
        return m_Rotation;
    }

    bool GameObject::GetVisible()
    {
        return m_Visible;
    }

    void GameObject::SetPosition(glm::vec2 position)
    {
        m_Position = { position, 0.0f };
        CalculateTransformMatrix();
    }

    void GameObject::SetSize(glm::vec2 size)
    {
        m_Size = { size.x, -size.y, 1.0f };
        CalculateTransformMatrix();
    }

    void GameObject::SetRotation(float angle)
    {
        m_Rotation = angle;
        CalculateTransformMatrix();
    }

    void GameObject::SetVisible(bool visible)
    {
        m_Visible = visible;
    }

    void GameObject::CalculateTransformMatrix()
    {
        m_Transform = glm::translate(glm::mat4(1.0f), m_Position)
            * glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), { 0.0f, 0.0f, 1.0f })
            * glm::scale(glm::mat4(1.0f), { m_Size.x, m_Size.y, 1.0f });
    }
}