/*
 *  Ray.cpp
 *  lapl
 *
 *  Created by jian zhang on 3/16/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#include "Ray.h"

Ray::Ray() {}

Ray::Ray(const Vector3F& pfrom, const Vector3F& vdir, float min, float max)
{
	m_origin = pfrom;
	m_dir = vdir;
	m_tmin = min;
	m_tmax = max;
}

Ray::Ray(const Vector3F& pfrom, const Vector3F& pto) 
{
	m_origin = pfrom;
	m_dir = pto - pfrom;
	m_tmin = 0.f;
	m_tmax = m_dir.length();
	m_dir.normalize();
}

Vector3F Ray::travel(float & t) const
{
	return m_origin + m_dir * t;
}

const Vector3F Ray::closetPointOnRay(const Vector3F & p, float * t) const
{
	float tt = m_origin.dot(m_dir) - p.dot(m_dir);
	if(t) *t = tt;
	return m_origin - m_dir * tt;
}
