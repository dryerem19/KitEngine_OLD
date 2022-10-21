//
// Created by dryerem19 on 10/21/22.
//

#include "Graphics/Shader.h"
#include "Graphics/Renderer.h"

//-------------------------------------------------------------------------------------------
// Конструктор
//-------------------------------------------------------------------------------------------
KitEngine::Graphics::Shader::Shader(const std::string &filename)
    : mFilename(filename), mShaderId(0) {

    ShaderProgramSource source = this->ParseShader(filename);
    mShaderId = this->CreateShader(source);

}

//-------------------------------------------------------------------------------------------
// Деструктор
//-------------------------------------------------------------------------------------------
KitEngine::Graphics::Shader::~Shader() {

    // Cleanup
    glDeleteProgram(mShaderId);

}

//-------------------------------------------------------------------------------------------
// Включить шейдер
//-------------------------------------------------------------------------------------------
void KitEngine::Graphics::Shader::Enable() const {

    glUseProgram(mShaderId);

}

//-------------------------------------------------------------------------------------------
// Отключить шейдер
//-------------------------------------------------------------------------------------------
void KitEngine::Graphics::Shader::Disable() {

    glUseProgram(0);

}

//-------------------------------------------------------------------------------------------
// Установка вектора униформ переменной
//-------------------------------------------------------------------------------------------
void KitEngine::Graphics::Shader::SetUniform4f(const std::string &uniformName, float x, float y, float z,
                                               float w) const {

    const GLint location = this->GetUniformLocation(uniformName);
    glUniform4f(location, x, y, z, w);

}

//-------------------------------------------------------------------------------------------
// Получение местоположения униформ переменной
// const std::string &uniformName - имя униформ переменной
// returned: местоположение переменной
//-------------------------------------------------------------------------------------------
GLint KitEngine::Graphics::Shader::GetUniformLocation(const std::string &uniformName) const {

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
unsigned int KitEngine::Graphics::Shader::CreateShader(const ShaderProgramSource& source) const {

    // Compile shaders
    const unsigned int idProgram      = glCreateProgram();
    const unsigned int idVertexShader = CompileShader(source.VertexSource, GL_VERTEX_SHADER);
    const unsigned int idPixelShader  = CompileShader(source.FragmentSource,GL_FRAGMENT_SHADER);

    // Link shaders
    glAttachShader(idProgram, idVertexShader);
    glAttachShader(idProgram, idPixelShader);

    glLinkProgram(idProgram);
    glValidateProgram(idProgram);

    // Cleanup
    glDeleteShader(idVertexShader);
    glDeleteShader(idPixelShader);

    return idProgram;

}

//-------------------------------------------------------------------------------------------
// Компиляция шейдера
// const std::string& shaderText - текст шейдера
// unsigned int type - тип шейдера
// returned: идентификатор шейдера
//-------------------------------------------------------------------------------------------
unsigned int KitEngine::Graphics::Shader::CompileShader(const std::string& shaderText, unsigned int type) const {

    // Create shader
    const unsigned int id = glCreateShader(type);

    // Compile shader
    const char* source = shaderText.c_str();
    glShaderSource(id, 1, &source, nullptr);
    glCompileShader(id);

    // Check if error
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (GL_FALSE == result) {

        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

        char* message = (char*) alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);

        // TODO: Please, write it to log
        std::cout << "Failed to compile" << (type == GL_VERTEX_SHADER ? "vertex" : "pixel")
                  << "shader!" << std::endl;
        std::cout << message << std::endl;

        /* Cleanup */
        glDeleteShader(id);

        return -1;
    }

    return id;

}

//-------------------------------------------------------------------------------------------
// Чтение шейдера из файла
// const std::string &shaderPath - путь к файлу шейдера
// returned: структура с текстом шейдера
//-------------------------------------------------------------------------------------------
KitEngine::Graphics::ShaderProgramSource KitEngine::Graphics::Shader::ParseShader(const std::string &shaderPath) {

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
            ss[static_cast<unsigned int>(type)] << line << "\n";
        }
    }

    return { ss[0].str(), ss[1].str() };

}