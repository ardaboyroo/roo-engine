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

// ImGui headers
#include "ImGui/ImGuiLayer.hpp"

// Event headers
#include "Events/ApplicationEvent.hpp"
#include "Events/KeyEvent.hpp"
#include "Events/MouseEvent.hpp"

// Third Party headers
#include "glm/glm.hpp"
#include "imgui.h"

// ------------Entry Point------------
#include "Core/EntryPoint.hpp"
// -----------------------------------