/*
 *  Vertex.h
 *  convexHull
 *
 *  Created by jian zhang on 9/5/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */
#pragma once
#include <Vector3F.h>
#include <GeoElement.h>
class Vertex : public GeoElement {
public:
	Vertex();
	virtual ~Vertex();
	
	Vector3F *m_v;
};