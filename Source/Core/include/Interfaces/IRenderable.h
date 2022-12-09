/**
 * @file IRenderable.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-12-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

class IRenderable
{
private:
    bool mVisible = true;
public:
    virtual ~IRenderable() = default;

    virtual void Show() { mVisible = true;  }
    virtual void Hide() { mVisible = false; }
    virtual bool IsVisible() const { return mVisible; }
    virtual void Draw() = 0;
};