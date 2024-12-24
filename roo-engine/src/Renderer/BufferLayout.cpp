#include "BufferLayout.hpp"

namespace roo
{
    void BufferLayout::CalculateOffsetsAndStride()
    {
        uint32_t offset = 0;
        m_Stride = 0;

        for (auto& element : m_Elements)
        {
            element.Offset = offset;
            offset += element.Size;
            m_Stride += element.Size;
        }
    }

    uint32_t BufferElement::GetComponentCount() const
    {
        switch (Type)
        {
        case ShaderDataType::Float:   return 1;
        case ShaderDataType::Float2:  return 2;
        case ShaderDataType::Float3:  return 3;
        case ShaderDataType::Float4:  return 4;
        case ShaderDataType::Int:     return 1;
        case ShaderDataType::Int2:    return 2;
        case ShaderDataType::Int3:    return 3;
        case ShaderDataType::Int4:    return 4;
        case ShaderDataType::Mat3:    return 3 * 3;
        case ShaderDataType::Mat4:    return 4 * 4;
        case ShaderDataType::Bool:    return 1;
        }

        ROO_LOG_ERROR("Unknown ShaderDataType!");
        return 0;
    }
}