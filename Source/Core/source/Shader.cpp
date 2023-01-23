//
// Created by dryerem19 on 10/21/22.
//
#include "pch.h"
#include "Shader.h"

//-------------------------------------------------------------------------------------------
// Конструктор
//-------------------------------------------------------------------------------------------
Shader::Shader(const std::string &filename)
    : mFilename(filename), mShaderId(0) {

    ShaderProgramSource source = this->ParseShader(filename);
    mShaderId = this->CreateShader(source);

}

//-------------------------------------------------------------------------------------------
// Деструктор
//-------------------------------------------------------------------------------------------
Shader::~Shader() {

    // Cleanup
    GLCall(glDeleteProgram(mShaderId));

}

//-------------------------------------------------------------------------------------------
// Включить шейдер
//-------------------------------------------------------------------------------------------
void Shader::Enable() const {

    GLCall(glUseProgram(mShaderId));

}

//-------------------------------------------------------------------------------------------
// Отключить шейдер
//-------------------------------------------------------------------------------------------
void Shader::Disable() {

    GLCall(glUseProgram(0));

}

//-------------------------------------------------------------------------------------------
// Установка матрицы 4x4 униформ переменной
//-------------------------------------------------------------------------------------------
void
Shader::SetUniformMatrix4fv(const std::string &uniformName, GLsizei count, GLboolean transpose,
                                                 const GLfloat *value) const {

    const GLint location = this->GetUniformLocation(uniformName);
    glUniformMatrix4fv(location, count, transpose, value);

}

void Shader::SetMat(const std::string &name, const glm::mat4 &mat)
{
    const GLint location = GetUniformLocation(name);
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::SetMat(const std::string &name, const glm::mat3 &mat)
{
    const GLint location = GetUniformLocation(name);
    glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(mat));
}

//-------------------------------------------------------------------------------------------
// Установка вектора униформ переменной
//-------------------------------------------------------------------------------------------
void Shader::SetUniform4f(const std::string &uniformName, float x, float y, float z,
                                               float w) const {

    const GLint location = this->GetUniformLocation(uniformName);
    GLCall(glUniform4f(location, x, y, z, w));

}

//-------------------------------------------------------------------------------------------
// Установка вектора (vec3) униформ переменной
//-------------------------------------------------------------------------------------------
void Shader::SetUniform3f(const std::string &uniformName, float x, float y, float z) const {

    const GLint location = this->GetUniformLocation(uniformName);
    GLCall(glUniform3f(location, x, y, z));

}

//-------------------------------------------------------------------------------------------
// Установка float значения
//-------------------------------------------------------------------------------------------
void Shader::SetUniform1f(const std::string &uniformName, float value)
{
    GLCall(glUniform1f(this->GetUniformLocation(uniformName), value));
}

//-------------------------------------------------------------------------------------------
// Получение местоположения униформ переменной
// const std::string &uniformName - имя униформ переменной
// returned: местоположение переменной
//-------------------------------------------------------------------------------------------
GLint Shader::GetUniformLocation(const std::string &uniformName) const {

    GLint location = glGetUniformLocation(mShaderId, uniformName.c_str());
    if (location == -1) {
        // TODO: Please, write error information to log, uniform doesn't exist
    }

    return location;

}

//-------------------------------------------------------------------------------------------
// Создание шейдера
// const ShaderProgramSource& source - структура с текстом шейдера
// returned: идентификатор шейдера
//-------------------------------------------------------------------------------------------
unsigned int Shader::CreateShader(const ShaderProgramSource& source) const {

    // Compile shaders
    const uint32_t idProgram      = glCreateProgram();
    const uint32_t idVertexShader = CompileShader(source.VertexSource, GL_VERTEX_SHADER);
    const uint32_t idPixelShader  = CompileShader(source.FragmentSource,GL_FRAGMENT_SHADER);

    // Link shaders
    GLCall(glAttachShader(idProgram, idVertexShader));
    GLCall(glAttachShader(idProgram, idPixelShader));

    GLCall(glLinkProgram(idProgram));
    GLCall(glValidateProgram(idProgram));

    // Cleanup
    GLCall(glDeleteShader(idVertexShader));
    GLCall(glDeleteShader(idPixelShader));

    return idProgram;

}

//-------------------------------------------------------------------------------------------
// Компиляция шейдера
// const std::string& shaderText - текст шейдера
// unsigned int type - тип шейдера
// returned: идентификатор шейдера
//-------------------------------------------------------------------------------------------
unsigned int Shader::CompileShader(const std::string& shaderText, uint32_t type) const {

    // Create shader
    const uint32_t id = glCreateShader(type);

    // Compile shader
    const char* source = shaderText.c_str();
    GLCall(glShaderSource(id, 1, &source, nullptr));
    GLCall(glCompileShader(id));

    // Check if error
    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (GL_FALSE == result) {

        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));

        char* message = (char*) alloca(length * sizeof(char));
        GLCall(glGetShaderInfoLog(id, length, &length, message));

        // TODO: Please, write it to log
        std::cout << "Failed to compile" << (type == GL_VERTEX_SHADER ? "vertex" : "pixel")
                  << "shader!" << std::endl;
        std::cout << message << std::endl;

        /* Cleanup */
        GLCall(glDeleteShader(id));

        return -1;
    }

    return id;

}

//-------------------------------------------------------------------------------------------
// Чтение шейдера из файла
// const std::string &shaderPath - путь к файлу шейдера
// returned: структура с текстом шейдера
//-------------------------------------------------------------------------------------------
ShaderProgramSource Shader::ParseShader(const std::string &shaderPath) {

    if (shaderPath.empty()) {
        return {"", ""};
    }

    std::ifstream stream(shaderPath);
    std::string line;
    std::stringstream ss[2];

    ShaderType type = ShaderType::NONE;
    while (getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos) {
                type = ShaderType::FRAGMENT;
            }
        }
        else if (type == ShaderType::VERTEX || type == ShaderType::FRAGMENT) {
            ss[static_cast<uint32_t>(type)] << line << "\n";
        }
    }

    return { ss[0].str(), ss[1].str() };

}


void Shader::SetUniform1i(const std::string &uniformName, int value) {

    GLCall(glUniform1i(this->GetUniformLocation(uniformName), value));

}
