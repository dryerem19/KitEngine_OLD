/**
 * @file Shape.h
 * @author Denis Eremenko (mamayma8@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-01-28
 * 
 * @copyright Copyright Denis Eremenko (c) 2023
 * 
 */
#pragma once

struct IShape
{
private:
    glm::vec3 mCenter;
protected:
    IShape(const glm::vec3& center) 
        : mCenter(center) {};
public:
    virtual void Render() = 0;
    virtual ~IShape() = 0;
};