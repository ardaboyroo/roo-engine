#include "Window.hpp"

#include "Log.hpp"

#include "Events/ApplicationEvent.hpp"
#include "Events/KeyEvent.hpp"
#include "Events/MouseEvent.hpp"

namespace roo
{
    static void rooGLFWErrorCallback(int error, const char* description)
    {
        ROO_LOG_ERROR("GLFW Error" + S(error) + ": " + description);
    }

    Window::Window(const EventCallbackFn& callback, const WindowSettings& settings)
        : m_GLFWWindow(nullptr)
    {
        SetEventCallback(callback);
        Init(settings);
    }

    Window::~Window()
    {
        Terminate();
    }

    void Window::OnUpdate()
    {
        glfwSwapBuffers(m_GLFWWindow);
        glfwPollEvents();
    }

    uint32_t Window::GetWidth() const
    {
        return m_Data.Width;
    }

    uint32_t Window::GetHeight() const
    {
        return m_Data.Height;
    }

    void Window::SetEventCallback(const EventCallbackFn& callback)
    {
        m_Data.EventCallback = callback;
    }

    void Window::SetVSync(bool enabled)
    {
        if (enabled)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);

        m_Data.VSyncEnabled = enabled;
    }

    bool Window::IsVSync() const
    {
        return m_Data.VSyncEnabled;
    }

    void Window::SetBackgroundColor(float r, float g, float b)
    {
        m_Data.BackgroundColor[0] = r;
        m_Data.BackgroundColor[1] = g;
        m_Data.BackgroundColor[2] = b;
        glClearColor(
            m_Data.BackgroundColor[0],      // Red
            m_Data.BackgroundColor[1],      // Green
            m_Data.BackgroundColor[2],      // Blue
            1.0f);                          // Alpha
    }

    void Window::Init(const WindowSettings& settings)
    {
        // Initialize window data
        m_Data.Title = settings.Title;
        m_Data.Width = settings.Width;
        m_Data.Height = settings.Height;
        m_Data.VSyncEnabled = settings.VSyncEnabled;

        m_Data.BackgroundColor[0] = 0.0f;
        m_Data.BackgroundColor[1] = 0.0f;
        m_Data.BackgroundColor[2] = 0.0f;


        ROO_LOG_INFO("Creating window \"" + m_Data.Title + "\", (" + 
            S(m_Data.Width) + 
            'x' + 
            S(m_Data.Height) + ')' +
            ", VSync: " + (m_Data.VSyncEnabled ? "ON" : "OFF")
        );


        int success = glfwInit();
        if (!success)
            ROO_LOG_ERROR("Could not initialize glfw");


        glfwSetErrorCallback(rooGLFWErrorCallback);
        // Create a GLFW Window
        m_GLFWWindow = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title.c_str(), NULL, NULL);
        glfwMakeContextCurrent(m_GLFWWindow);
        int GLADstatus = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        if (!GLADstatus)
            ROO_LOG_ERROR("Could not initialize GLAD");
        glfwSetWindowUserPointer(m_GLFWWindow, &m_Data);
        SetVSync(m_Data.VSyncEnabled);


        // Set GLFW callbacks
        glfwSetWindowCloseCallback(m_GLFWWindow, [](GLFWwindow* window)
            {
                WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
                WindowCloseEvent event;
                data.EventCallback(event);
            });

        glfwSetWindowSizeCallback(m_GLFWWindow, [](GLFWwindow* window, int width, int height)
            {
                WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
                data.Width = width;
                data.Height = height;

                WindowResizeEvent event(width, height);
                data.EventCallback(event);
            });

        glfwSetKeyCallback(m_GLFWWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods)
            {
                WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

                switch (action)
                {
                    case GLFW_PRESS:
                    {
                        KeyPressedEvent event(key);
                        data.EventCallback(event);
                        break;
                    }
                    case GLFW_REPEAT:
                    {
                        KeyPressedEvent event(key, true);
                        data.EventCallback(event);
                        break;
                    }
                    case GLFW_RELEASE:
                    {
                        KeyReleasedEvent event(key);
                        data.EventCallback(event);
                        break;
                    }
                }
            });

        glfwSetMouseButtonCallback(m_GLFWWindow, [](GLFWwindow* window, int button, int action, int mods)
            {
                WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

                switch (action)
                {
                    case GLFW_PRESS:
                    {
                        MouseButtonPressedEvent event(button);
                        data.EventCallback(event);
                        break;
                    }
                    case GLFW_RELEASE:
                    {
                        MouseButtonReleasedEvent event(button);
                        data.EventCallback(event);
                        break;
                    }
                }
            });

        glfwSetScrollCallback(m_GLFWWindow, [](GLFWwindow* window, double xOffset, double yOffset)
            {
                WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

                MouseScrolledEvent event((float)xOffset, (float)yOffset);
                data.EventCallback(event);
            });

        glfwSetCursorPosCallback(m_GLFWWindow, [](GLFWwindow* window, double xPos, double yPos)
            {
                WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

                MouseMovedEvent event((float)xPos, (float)yPos);
                data.EventCallback(event);
            });
    }

    void Window::Terminate()
    {
        glfwDestroyWindow(m_GLFWWindow);
        glfwTerminate();
    }
}