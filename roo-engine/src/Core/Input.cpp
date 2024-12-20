#include "Input.hpp"

#include "Core/Application.hpp"
#include "Core/Window.hpp"

#include <GLFW/glfw3.h>

namespace roo
{
    bool Input::IsKeyPressed(int keycode)
    {
        GLFWwindow* window = Application::Get().GetWindow().m_GLFWWindow;
        int state = glfwGetKey(window, keycode);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool Input::IsMouseButtonPressed(int button)
    {
        GLFWwindow* window = Application::Get().GetWindow().m_GLFWWindow;
        int state = glfwGetMouseButton(window, button);
        return state == GLFW_PRESS;
    }

    std::pair<float, float> Input::GetMousePosition()
    {
        GLFWwindow* window = Application::Get().GetWindow().m_GLFWWindow;
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        return { (float)xpos, (float)ypos };
    }

    float Input::GetMouseX()
    {
        auto[x, y] = GetMousePosition();
        return x;
    }

    float Input::GetMouseY()
    {
        auto[x, y] = GetMousePosition();
        return y;
    }
}