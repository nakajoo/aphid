/*
 *  BaseFunction.h
 *  aphid
 *
 *  Created by jian zhang on 10/26/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once
#include <AllMath.h>
class BaseFunction {
public:
	BaseFunction();
	virtual ~BaseFunction();
	
	virtual double f(const Vector2F & x);
	
	float particalDerivativeAt(float x, const Vector2F & at, const Vector2F & S);
	
	float minimization(const Vector2F & x, const Vector2F & part);
private:
	
};