#pragma once

#include "glm/glm.hpp"

typedef unsigned int GLenum;

namespace roo
{
    class Shader
    {
    public:
        Shader(const std::string& filepath);
        Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
        ~Shader();

        void Bind();
        void Unbind();


        void SetUniformInt(const std::string& name, int value);

        void SetUniformFloat(const std::string& name, float value);
        void SetUniformFloat2(const std::string& name, const glm::vec2& value);
        void SetUniformFloat3(const std::string& name, const glm::vec3& value);
        void SetUniformFloat4(const std::string& name, const glm::vec4& value);

        void SetUniformMat3(const std::string& name, const glm::mat3& matrix);
        void SetUniformMat4(const std::string& name, const glm::mat4& matrix);

    private:
        std::string ReadFile(const std::string& filepath);
        std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
        void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);

        uint32_t m_RendererID;
    };
}