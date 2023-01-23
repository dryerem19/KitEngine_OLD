/**
 * @file GLMotionState.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-01-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include <btBulletCollisionCommon.h>

class GLMotionState : public btDefaultMotionState 
{
public:
    GLMotionState(const btTransform &transform) : btDefaultMotionState(transform) {}

	void GetWorldTransform(btScalar* transform) 
    {
		btTransform trans;
		getWorldTransform(trans);
		trans.getOpenGLMatrix(transform);
	}
};