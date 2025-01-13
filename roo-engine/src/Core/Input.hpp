#pragma once

namespace roo
{
    // In order to receive input, poll in your OnUpdate function in a layer.
    // If you want to receive input events instead of polling check out the 
    // OnEvent function in layer with KeyEvent and MouseEvent.
    class Input
    {
    public:
        static bool IsKeyPressed(int keycode);
        static bool IsMouseButtonPressed(int button);
        static std::pair<float, float> GetMousePosition();
        static float GetMouseX();
        static float GetMouseY();
    };
}