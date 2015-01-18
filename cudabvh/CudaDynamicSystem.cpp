#include "CudaDynamicSystem.h"
#include <CUDABuffer.h>
CudaDynamicSystem::CudaDynamicSystem() 
{
    m_X = new CUDABuffer;
    m_V = new CUDABuffer;
    m_F = new CUDABuffer;
}

CudaDynamicSystem::~CudaDynamicSystem() {}

void CudaDynamicSystem::setNumPoints(unsigned n)
{ m_numPoints = n; }

const unsigned CudaDynamicSystem::numPoints() const
{ return m_numPoints; }

void CudaDynamicSystem::initOnDevice()
{
    m_X->create(numPoints() * 12);
    m_V->create(numPoints() * 12);
    m_F->create(numPoints() * 12);
}

void CudaDynamicSystem::update(float dt) {}

void * CudaDynamicSystem::positionOnDevice()
{ return m_X->bufferOnDevice(); }

void * CudaDynamicSystem::velocityOnDevice()
{ return m_V->bufferOnDevice(); }

void * CudaDynamicSystem::forceOnDevice()
{ return m_F->bufferOnDevice(); }

CUDABuffer * CudaDynamicSystem::X()
{ return m_X; }

CUDABuffer * CudaDynamicSystem::V()
{ return m_V; }

CUDABuffer * CudaDynamicSystem::F()
{ return m_F; }

