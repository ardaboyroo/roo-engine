#pragma once

#include "VertexArray.hpp"
#include "Shader.hpp"
#include "Camera.hpp"

namespace roo
{
    class Renderer
    {
    public:
        static void BeginScene();
        static void EndScene();

        static void Clear();

        static void Draw(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray);
    };
}