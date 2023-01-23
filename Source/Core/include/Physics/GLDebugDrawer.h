/**
 * @file GLDebugDrawer.h
 * @author Denis Eremenko (mamayma8@gmail.com)
 * @brief Bullet Physics debug
 * @version 0.1
 * @date 2022-12-26
 * 
 * @copyright Denis Eremenko Copyright (c) 2022
 * 
 */
#pragma once
#include "RenderBackend.h"

class GLDebugDrawer final : public btIDebugDraw 
{
private:
    int mDebugMode;


    btVector3 mFromLine;
    btVector3 mToLine;

    unsigned int mVaoId;
    unsigned int mVboId;    

    std::shared_ptr<Shader> mShader;    


public:
    GLDebugDrawer();

	virtual void setDebugMode(int debugMode) override final { mDebugMode = debugMode; }
	virtual int getDebugMode() const override final { return mDebugMode; }

    // unused
    virtual void drawContactPoint(const btVector3 &pointOnB, const btVector3 &normalOnB, btScalar distance, int lifeTime, const btVector3 &color) override final;
    
    virtual void drawLine(const btVector3 &from, const btVector3 &to, const btVector3 &color) override final;

	// unused
	virtual void  reportErrorWarning(const char* warningString) override {}
    // unused
	virtual void  draw3dText(const btVector3 &location,const char* textString) override {}   
};