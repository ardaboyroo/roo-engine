#include "VertexArray.hpp"

namespace roo
{
    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
    {
        switch (type)
        {
        case roo::ShaderDataType::Float:    return GL_FLOAT;
        case roo::ShaderDataType::Float2:   return GL_FLOAT;
        case roo::ShaderDataType::Float3:   return GL_FLOAT;
        case roo::ShaderDataType::Float4:   return GL_FLOAT;
        case roo::ShaderDataType::Int:      return GL_INT;
        case roo::ShaderDataType::Int2:     return GL_INT;
        case roo::ShaderDataType::Int3:     return GL_INT;
        case roo::ShaderDataType::Int4:     return GL_INT;
        case roo::ShaderDataType::Mat3:     return GL_FLOAT;
        case roo::ShaderDataType::Mat4:     return GL_FLOAT;
        case roo::ShaderDataType::Bool:     return GL_BOOL;
        }

        ROO_LOG_ERROR("Unknown ShaderDataType!");
        return 0;
    }

    VertexArray::VertexArray()
    {
        glCreateVertexArrays(1, &m_RendererID);
    }

    VertexArray::~VertexArray()
    {
        glDeleteVertexArrays(1, &m_RendererID);
    }

    void VertexArray::Bind() const
    {
        glBindVertexArray(m_RendererID);
    }

    void VertexArray::Unbind() const
    {
        glBindVertexArray(0);
    }

    void VertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
    {
        if (vertexBuffer->GetLayout().GetElements().size() == 0)
            ROO_LOG_ERROR("Vertex buffer has no layout");

        glBindVertexArray(m_RendererID);
        vertexBuffer->Bind();

        uint32_t index = 0;
        const auto& layout = vertexBuffer->GetLayout();
        for (const auto& element : layout)
        {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index,
                element.GetComponentCount(),
                ShaderDataTypeToOpenGLBaseType(element.Type),
                element.Normalized ? GL_TRUE : GL_FALSE,
                layout.GetStride(),
                (const void*)element.Offset);
            index++;
        }

        m_VertexBuffers.push_back(vertexBuffer);
    }

    void VertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
    {
        glBindVertexArray(m_RendererID);
        indexBuffer->Bind();

        m_IndexBuffer = indexBuffer;
    }
}