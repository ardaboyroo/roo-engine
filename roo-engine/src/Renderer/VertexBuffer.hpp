#pragma once

#include "BufferLayout.hpp"

namespace roo
{
    class VertexBuffer
    {
    public:
        VertexBuffer(void* vertices, uint32_t size);
        ~VertexBuffer();

        void Bind();
        void Unbind();

        inline const BufferLayout& GetLayout() const { return m_Layout; }
        inline void SetLayout(const BufferLayout& layout) { m_Layout = layout; }

    private:
        uint32_t m_RendererID;
        BufferLayout m_Layout;
    };
}