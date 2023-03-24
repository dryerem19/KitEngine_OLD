//
// Created by dryerem19 on 10/21/22.
//

#pragma once

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
    uint32_t mShaderId;
public:
    explicit Shader(const std::string& filename);
    ~Shader();
    void Enable() const;
    void Disable();
    void SetUniform1i(const std::string& uniformName, int value);
    void SetUniform1f(const std::string& uniformName, float value);
    void SetUniform4f(const std::string& uniformName, float x, float y, float z, float w) const;
    void SetUniform3f(const std::string &uniformName, float x, float y, float z) const;
    void SetUniformMatrix4fv(const std::string& uniformName, GLsizei count, GLboolean transpose,
                                const GLfloat *value) const;

    void Bind();
    void UnBind();
    bool SetMat(const std::string& name, const glm::mat4& mat);
    bool SetMat(const std::string& name, const glm::mat3& mat);
    bool SetVec(const std::string& name, const glm::vec2& vec);
    bool SetVec(const std::string& name, const glm::vec3& vec);
    bool SetVec(const std::string& name, const glm::vec4& vec);
    bool SetFloat(const std::string& name, const float& value);
    bool SetInt(const std::string& name, const int& value);
    
private:
    [[nodiscard]] GLint GetUniformLocation(const std::string& uniformName) const;
    [[nodiscard]] unsigned int CreateShader(const ShaderProgramSource& source) const;
    [[nodiscard]] unsigned int CompileShader(const std::string& shaderText, unsigned int type) const;
    ShaderProgramSource ParseShader(const std::string& shaderPath);
};