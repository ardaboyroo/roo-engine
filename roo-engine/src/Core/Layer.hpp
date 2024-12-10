#pragma once

#include "Events/Event.hpp"

#include <string>

namespace roo
{

	class Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(roo::Event& event) {}

		const std::string& GetName() const { return m_LayerName; }
	protected:
		std::string m_LayerName;
	};

}