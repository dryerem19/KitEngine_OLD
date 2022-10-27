//
// Created by dryerem19 on 10/21/22.
//

#pragma once
#include "KitEnginePch.h"

namespace KitEngine::Graphics
{
    struct ShaderProgramSource
    {
        std::string VertexSource;
        std::string FragmentSource;
    };

    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    class Shader
    {
    private:
        std::string mFilename;
        unsigned int mShaderId;
    public:
        explicit Shader(const std::string& filename);
        ~Shader();
        void Enable() const;
        void Disable();
        void SetUniform1i(const std::string& uniformName, int value);
        void SetUniform4f(const std::string& uniformName, float x, float y, float z, float w) const;
        void SetUniformMatrix4fv(const std::string& uniformName, GLsizei count, GLboolean transpose,
                                 const GLfloat *value) const;
    private:
        [[nodiscard]] GLint GetUniformLocation(const std::string& uniformName) const;
        [[nodiscard]] unsigned int CreateShader(const ShaderProgramSource& source) const;
        [[nodiscard]] unsigned int CompileShader(const std::string& shaderText, unsigned int type) const;
        ShaderProgramSource ParseShader(const std::string& shaderPath);
    };
}