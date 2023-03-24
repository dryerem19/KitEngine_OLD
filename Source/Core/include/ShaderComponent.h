/**
 * @file ShaderComponent.h
 * @author Denis Eremenko (mamayma8@gmail.com)
 * @brief Shader component interface
 * @version 0.1
 * @date 2023-01-31
 * 
 * @copyright Copyright Denis Eremenko  (c) 2023
 * 
 */
#pragma once
#include "Shader.h"

class ShaderComponent
{
private:
    std::shared_ptr<Shader>& mShader;
public:
    ShaderComponent(std::shared_ptr<Shader>& shader);
    void SetShader(std::shared_ptr<Shader>& shader);
    std::shared_ptr<Shader>& GetShader() const;
};