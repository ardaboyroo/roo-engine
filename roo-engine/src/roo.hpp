#pragma once

// This header is for use by roo-engine applications

// Example:
////////////////////////////////////
//
// #include <roo.hpp>
//
// class MyApp : public roo::Application
// {
//     ...
// }
//
// roo::Application* roo::CreateApplication()
// {
//     return new MyApp();
// }
//
///////////////////////////////////

// Core headers
#include "Core/Core.hpp"
#include "Core/Application.hpp"
#include "Core/Log.hpp"
#include "Core/Layer.hpp"
#include "Core/Input.hpp"
#include "Core/KeyCodes.hpp"
#include "Core/MouseCodes.hpp"
#include "Core/Texture.hpp"
#include "Core/GameObject.hpp"
#include "Core/Sprite.hpp"
#include "Core/Rectangle.hpp"

// ImGui headers
#include "ImGui/ImGuiLayer.hpp"

// Event headers
#include "Events/Event.hpp"
#include "Events/ApplicationEvent.hpp"
#include "Events/KeyEvent.hpp"
#include "Events/MouseEvent.hpp"

// Renderer headers
#include "Renderer/Renderer.hpp"
#include "Renderer/VertexArray.hpp"
#include "Renderer/VertexBuffer.hpp"
#include "Renderer/BufferLayout.hpp"
#include "Renderer/IndexBuffer.hpp"
#include "Renderer/Shader.hpp"
#include "Renderer/Camera.hpp"

// Util headers
#include "Utils/Utils.hpp"
#include "Utils/Audio.hpp"

// Third Party headers
#include "glm/glm.hpp"
#include "imgui.h"

// ------------Entry Point------------
#include "Core/EntryPoint.hpp"
// -----------------------------------