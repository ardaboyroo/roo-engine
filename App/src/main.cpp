#include "roo.hpp"

#include <memory>

// IMPORTANT! : To run this demo make sure the assets folder located in root/App/assets
// is copied to the according build directory (e.g. root/build/bin/App/Debug/assets)

class PongLayer : public roo::Layer
{
public:
    PongLayer()
        : Layer("PongLayer"), window(roo::Application::Get().GetWindow())
    {
        // Heaps and globals are not shared across DLL boundaries! 
        // You will need to call SetCurrentContext() + SetAllocatorFunctions()
        ImGui::SetCurrentContext(roo::Application::Get().GetImGuiContext());
    }

    void OnAttach()
    {
        paddle1 = std::make_shared<roo::Rectangle>(glm::vec2(20, 100), glm::vec2(10, 100), glm::vec3(.8, .1, .3));
        AddGameObject(paddle1);

        paddle2 = std::make_shared<roo::Rectangle>(glm::vec2(20, 100), 
            glm::vec2(window.GetWidth() - 10, 100), glm::vec3(.3, .1, .8));
        AddGameObject(paddle2);

        ball = std::make_shared<roo::Sprite>("assets/ball.png");
        ball->SetPosition({ window.GetWidth() / 2.f, window.GetHeight() / 2.f});
        ball->SetSize({32, 32});
        AddGameObject(ball);
    }

    void OnUpdate(float deltaTime) override
    {
        // Paddle 1 movement
        {
            glm::vec2 pos = paddle1->GetPosition();
            if (roo::Input::IsKeyPressed(roo::Key::W))
                pos.y = glm::clamp(pos.y - paddleSpeed, 50.f, window.GetHeight() - 50.f);

            if (roo::Input::IsKeyPressed(roo::Key::S))
                pos.y = glm::clamp(pos.y + paddleSpeed, 50.f, window.GetHeight() - 50.f);

            paddle1->SetPosition(pos);
        }

        // Paddle 2 movement
        {
            glm::vec2 pos = paddle2->GetPosition();
            if (roo::Input::IsKeyPressed(roo::Key::Up))
                pos.y = glm::clamp(pos.y - paddleSpeed, 50.f, window.GetHeight() - 50.f);

            if (roo::Input::IsKeyPressed(roo::Key::Down))
                pos.y = glm::clamp(pos.y + paddleSpeed, 50.f, window.GetHeight() - 50.f);

            paddle2->SetPosition(pos);
        }

        // Paddle 1 Ball collision
        if (ball->GetPosition().x <= 29.f)
            if (glm::abs(paddle1->GetPosition().y - ball->GetPosition().y) <= 50.f)
            {
                ballVelocity.x *= -1.1;
                roo::Audio::Play("assets/Bounce.wav");
            }
        
        // Paddle 2 Ball collision
        if (ball->GetPosition().x >= window.GetWidth() - 29.f)
            if (glm::abs(paddle2->GetPosition().y - ball->GetPosition().y) <= 50.f)
            {
                ballVelocity.x *= -1.1;
                roo::Audio::Play("assets/Bounce.wav");
            }

        // Ball bounds collision
        if (ball->GetPosition().y <= 16.f || ball->GetPosition().y >= window.GetHeight() - 16.f)
            ballVelocity.y *= -1.f;

        // Ball rotation
        ball->SetRotation(ball->GetRotation() + 3.f);

        // Ball reset and score
        if (ball->GetPosition().x <= -16.f || ball->GetPosition().x >= window.GetWidth() + 16.f)
        {
            if (ball->GetPosition().x <= -16.f)
                scoreP2++;
            else
                scoreP1++;

            ballVelocity = { -5.f, 1.f};
            ball->SetPosition({ window.GetWidth() / 2.f, window.GetHeight() / 2.f });

            roo::Audio::Play("assets/Win.wav");
        }

        // Ball position update
        ball->SetPosition(ball->GetPosition() + ballVelocity);
    }

    void OnEvent(roo::Event& event) override
    {
    }

    void OnImGuiRender() override
    {
        // Create an ImGui window called Debug
        ImGui::Begin("Debug");

        // Add the framerate as a text
        std::string s = "Framerate: ";
        s += S(ImGui::GetIO().Framerate);
        ImGui::Text(s.c_str());

        // Display the scores
        ImGui::Text(("Red Score: " + S(scoreP1)).c_str());
        ImGui::Text(("Blue Score: " + S(scoreP2)).c_str());
        ImGui::End();
    }

private:
    std::shared_ptr<roo::Rectangle> paddle1;
    std::shared_ptr<roo::Rectangle> paddle2;

    std::shared_ptr<roo::Sprite> ball;
    glm::vec2 ballVelocity = {-5.0f, 1.0f};

    const float paddleSpeed = 5.0f;

    int scoreP1 = 0;
    int scoreP2 = 0;

    roo::Window& window;
};

class MyApp : public roo::Application
{
public:
    MyApp()
        // Initialize the application
        : Application(roo::WindowSettings(
            "Pong!",
            800,
            600,
            true)
        )
    {
        // Create and push a new layer, this will be the main working environment
        PushLayer(new PongLayer());
    }
};

roo::Application* roo::CreateApplication()
{
    // Create a new application and send it to the engine
    return new MyApp();
}