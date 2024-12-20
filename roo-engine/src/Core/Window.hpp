#pragma once

#include "Events/Event.hpp"

#include <string>

struct GLFWwindow;

namespace roo
{
    using EventCallbackFn = std::function<void(Event&)>;

    struct WindowSettings
    {
        std::string Title;
        uint32_t Width;
        uint32_t Height;
        bool VSyncEnabled;

        WindowSettings(const std::string& title = "roo engine",
            uint32_t width = 1280,
            uint32_t height = 720,
            bool vsync = true
        )
            : Title(title),
            Width(width),
            Height(height),
            VSyncEnabled(vsync)
        {
        }
    };

    class Application;
    class Window
    {
    public:
        Window(const EventCallbackFn& callback, const WindowSettings& settings = WindowSettings());
        ~Window();

        void OnUpdate();

        uint32_t GetWidth() const;
        uint32_t GetHeight() const;

        void SetEventCallback(const EventCallbackFn& callback);
        void SetVSync(bool enabled);
        bool IsVSync() const;

        void SetBackgroundColor(float r, float g, float b);

    private:
        void Terminate();
        void Init(const WindowSettings& settings);

        struct WindowData
        {
            std::string Title;
            uint32_t Width;
            uint32_t Height;
            bool VSyncEnabled;

            float BackgroundColor[3];

            EventCallbackFn EventCallback;
        };

    private:
        GLFWwindow* m_GLFWWindow;

        friend class ImGuiLayer;
        friend class Input;

        WindowData m_Data;
    };
}