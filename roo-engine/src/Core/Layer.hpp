#pragma once

#include "Events/Event.hpp"
#include "GameObject.hpp"

#include <string>
#include <memory>

namespace roo
{
    // This is the main class to work with if you want to receive updates and events.
    // Inherit from roo::Layer and push your layer to roo::Aplication to register it.
    // Layers will be called in the order you push. Every gameobject added will be 
    // relative to the layer.
    class Layer
    {
    public:
        Layer(const std::string& name = "Layer");
        virtual ~Layer() = default;

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate(float deltaTime) {}
        virtual void OnImGuiRender() {}
        virtual void OnEvent(roo::Event& event) {}

        void AddGameObject(std::shared_ptr<GameObject> object);
        std::vector<std::shared_ptr<GameObject>>& GetChildren();

        const std::string& GetName() const { return m_LayerName; }
    protected:
        std::string m_LayerName;

    private:
        std::vector<std::shared_ptr<GameObject>> m_Children;
    };

}