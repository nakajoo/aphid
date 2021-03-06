/*
 *  BuildKdTreeStream.cpp
 *  kdtree
 *
 *  Created by jian zhang on 10/29/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "BuildKdTreeStream.h"

BuildKdTreeStream::BuildKdTreeStream() {}
BuildKdTreeStream::~BuildKdTreeStream() 
{
	cleanup();
}

void BuildKdTreeStream::cleanup()
{
	m_indices.clear();
	m_nodes.clear();
	m_indirection.clear();
}

void BuildKdTreeStream::appendMesh(BaseMesh* mesh)
{
    if(mesh->isPatchMesh())
		printf("is patch mesh\n");
    
	unsigned numFace = mesh->getNumFaces();
	m_primitives.expandBy(numFace);
	m_indices.expandBy(numFace);

	for(unsigned i = 0; i < numFace; i++) {
		Primitive *p = m_primitives.asPrimitive();
		p->setGeometry((char *)mesh);
		p->setComponentIndex(i);
		unsigned *dest = m_indices.asIndex();
		*dest = m_primitives.index();
		m_primitives.next();
		m_indices.next();
	}
}

const unsigned BuildKdTreeStream::getNumPrimitives() const
{
	return m_primitives.index();
}

const PrimitiveArray &BuildKdTreeStream::getPrimitives() const
{
	return m_primitives;
}

const IndexArray &BuildKdTreeStream::getIndices() const
{
	return m_indices;
}

PrimitiveArray &BuildKdTreeStream::primitives()
{
	return m_primitives;
}
	
IndexArray &BuildKdTreeStream::indices()
{
	return m_indices;
}

IndexArray &BuildKdTreeStream::indirection()
{
	return m_indirection;
}

KdTreeNode *BuildKdTreeStream::createTreeBranch()
{
	KdTreeNode *p = (KdTreeNode *)m_nodes.expandBy(2);
	unsigned long * tmp = (unsigned long*)m_nodes.current();
	tmp[1] = tmp[3] = 6;
	m_nodes.next();
	tmp = (unsigned long*)m_nodes.current();
	tmp[1] = tmp[3] = 6;
	m_nodes.next();
	return p;
}

KdTreeNode *BuildKdTreeStream::firstTreeBranch()
{
	return m_nodes.asKdTreeNode(0);
}

void BuildKdTreeStream::verbose() const
{
	printf("kd-tree data stream input primitive count: %i\nnodes state:\n", getNumPrimitives());	
	m_nodes.verbose();
	printf("indirection state:\n");
	m_indirection.verbose();
}
