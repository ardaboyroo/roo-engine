#pragma once

#include "VertexArray.hpp"

namespace roo
{
    class Renderer
    {
    public:
        static void Clear();

        static void Draw(const std::shared_ptr<VertexArray>& vertexArray);
    };
}