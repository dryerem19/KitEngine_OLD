/**
 * @file Line.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-12-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "pch.h"
#include "Primitives/Line.h"

Line::Line(const glm::vec3 &start, const glm::vec3 &end, const glm::vec3& color /* = glm::vec4(1.f, 0.f, 0.f) */)
    : mStart(start), mEnd(end), mColor(color), mMvp(1.0f)
{
    std::vector<glm::vec3> vertices = {
        start, end
    };

    mShader = Core::ResourceManager::Instance().GetShader("../../Resources/shaders/line.glsl");

    auto layout = Render::VertexBufferLayout();
    layout.AddFloatElement(3);
    mVertexArray.AddBuffer(Render::VertexBuffer(vertices.data(), vertices.size() * sizeof(vertices[0])), layout);
}

void Line::SetColor(const glm::vec3 &color)
{
    mColor = color;
}

void Line::SetMVP(const glm::mat4 &mvp)
{
    mMvp = mvp;
}

void Line::Draw() const 
{
    mShader->Enable();
    mShader->SetUniformMatrix4fv("MVP", 1, GL_FALSE, glm::value_ptr(mMvp));
    mShader->SetUniform3f("color", mColor.x, mColor.y, mColor.z);

    mVertexArray.Bind();
    GLCall(glDrawArrays(GL_LINE_STRIP, 0, 2));
    //mVertexArray.Unbind();

    //mShader->Disable();
}