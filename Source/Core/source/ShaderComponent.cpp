/**
 * @file ShaderComponent.cpp
 * @author Denis Eremenko (mamayma8@gmail.com)
 * @brief Shader component implementation
 * @version 0.1
 * @date 2023-01-31
 * 
 * @copyright Copyright Denis Eremenko  (c) 2023
 * 
 */
#include "pch.h"
#include "ShaderComponent.h"

ShaderComponent::ShaderComponent(std::shared_ptr<Shader> &shader)
    : mShader(shader)
{
}

void ShaderComponent::SetShader(std::shared_ptr<Shader> &shader)
{
    mShader = shader;
}

std::shared_ptr<Shader> &ShaderComponent::GetShader() const
{
    return mShader;
}
