/*
 *  GLight.h
 *  mallard
 *
 *  Created by jian zhang on 9/18/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef G_LIGHT_H
#define G_LIGHT_H

#include <AllMath.h>

#ifdef WIN32
#include <windows.h>
#include <GL/gl.h>
#else
#include <gl_heads.h>
#endif
class GLight {
public:
	GLight();
		
	GLight(GLenum LightID, 
		Color4 Ambient, 
		Color4 Diffuse,
		Color4 Specular,
		Float4 Position);
 
    void activate() const;
	void deactivate() const;
    GLenum m_LightID;
    Color4 m_Ambient;
    Color4 m_Diffuse;
    Color4 m_Specular;
    Float4 m_Position;

};

#endif