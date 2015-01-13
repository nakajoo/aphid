#include <QtGui>

#include <gl_heads.h>
#include "glwidget.h"

#include <KdTreeDrawer.h>
#include <CUDABuffer.h>
#include <BvhSolver.h>
#include "bvh_common.h"
#include <radixsort_implement.h>
#include <app_define.h>
#include <CudaBase.h>

#define IDIM 101
#define IDIM1 102
#define IRAYDIM 42

GLWidget::GLWidget(QWidget *parent) : Base3DView(parent)
{
	m_solver = new BvhSolver;
	m_displayLevel = 0;
	
	m_displayVertex = new BaseBuffer;
	m_displayVertex->create(numVertices() * 12);
	
	m_triangleIndices = new BaseBuffer;
	m_triangleIndices->create(numTriangleFaceVertices() * 4);
	
// i,j  i1,j  
// i,j1 i1,j1
//
// i,j  i1,j  
// i,j1
//		i1,j  
// i,j1 i1,j1

	unsigned i, j, i1, j1;
	unsigned *ind = (unsigned *)m_triangleIndices->data();
	for(j=0; j < IDIM; j++) {
	    j1 = j + 1;
		for(i=0; i < IDIM; i++) {
		    i1 = i + 1;
			*ind = j * IDIM1 + i;
			ind++;
			*ind = j1 * IDIM1 + i;
			ind++;
			*ind = j * IDIM1 + i1;
			ind++;

			*ind = j * IDIM1 + i1;
			ind++;
			*ind = j1 * IDIM1 + i;
			ind++;
			*ind = j1 * IDIM1 + i1;
			ind++;
		}
	}
	
	m_edges = new BaseBuffer;
	m_edges->create(numEdges() * sizeof(EdgeContact));
	
	EdgeContact * edge = (EdgeContact *)m_edges->data();
	
	for(j=0; j < IDIM1; j++) {
	    j1 = j + 1;
		for(i=0; i < IDIM; i++) {
		    i1 = i + 1;
		    if(j==0) {
		        edge->v[0] = i1;
		        edge->v[1] = i;
		        edge->v[2] = IDIM1 + i;
		        edge->v[3] = MAX_INDEX;
		    }
		    else if(j==IDIM) {
		        edge->v[0] = j * IDIM1 + i;
		        edge->v[1] = j * IDIM1 + i1;
		        edge->v[2] = (j - 1) * IDIM1 + i1;
		        edge->v[3] = MAX_INDEX;
		    }
		    else {
		        edge->v[0] = j * IDIM1 + i;
		        edge->v[1] = j * IDIM1 + i1;
		        edge->v[2] = (j - 1) * IDIM1 + i1;
		        edge->v[3] = j1 * IDIM1 + i;
		    }
		    edge++;
		}
	}
	
	for(j=0; j < IDIM; j++) {
	    j1 = j + 1;
		for(i=0; i < IDIM1; i++) {
		    i1 = i + 1;
		    if(i==0) {
		        edge->v[0] = j * IDIM1 + i;
		        edge->v[1] = j1 * IDIM1 + i;
		        edge->v[2] = j * IDIM1 + i1;
		        edge->v[3] = MAX_INDEX;
		    }
		    else if(i==IDIM) {
		        edge->v[0] = j1 * IDIM1 + i;
		        edge->v[1] = j * IDIM1 + i;
		        edge->v[2] = j1 * IDIM1 + i - 1;
		        edge->v[3] = MAX_INDEX;
		    }
		    else {
		        edge->v[0] = j1 * IDIM1 + i;
		        edge->v[1] = j * IDIM1 + i;
		        edge->v[2] = j1 * IDIM1 + i - 1;
		        edge->v[3] = j * IDIM1 + i1;
		    }
		    edge++;
		}
	}
	
	for(j=0; j < IDIM; j++) {
	    j1 = j + 1;
		for(i=0; i < IDIM; i++) {
		    i1 = i + 1;
		    edge->v[0] = j1 * IDIM1 + i;
		    edge->v[1] = j * IDIM1 + i1;
		    edge->v[2] = j  * IDIM1 + i;
		    edge->v[3] = j1 * IDIM1 + i1;
			edge++;
		}
	}
	
	m_displayRays = new BaseBuffer;
	m_displayRays->create(IRAYDIM * IRAYDIM * sizeof(RayInfo));
	
	qDebug()<<"num vertoces "<<numVertices();
	qDebug()<<"num triangles "<<numTriangles();
	qDebug()<<"num edges "<<numEdges();
}

GLWidget::~GLWidget()
{
}

const unsigned GLWidget::numVertices() const 
{ return IDIM1 * IDIM1; }

const unsigned GLWidget::numTriangles() const
{ return IDIM * IDIM * 2; }

const unsigned GLWidget::numTriangleFaceVertices() const
{ return numTriangles() * 3; }

const unsigned GLWidget::numEdges() const
{ return IDIM * IDIM1 + IDIM * IDIM1 + IDIM * IDIM; }

void GLWidget::clientInit()
{
	CudaBase::SetDevice();
	m_solver->setPlaneUDim(IDIM);
	m_solver->createPoint(numVertices());
	m_solver->createEdges(m_edges, numEdges());
	m_solver->createRays(IRAYDIM, IRAYDIM);
	m_solver->init();
	//m_cvs->create(m_curve->numVertices() * 12);
	//m_cvs->hostToDevice(m_curve->m_cvs, m_curve->numVertices() * 12);
	//m_program->run(m_vertexBuffer, m_cvs, m_curve);
	connect(internalTimer(), SIGNAL(timeout()), m_solver, SLOT(simulate()));
	connect(m_solver, SIGNAL(doneStep()), this, SLOT(update()));
	// connect(internalTimer(), SIGNAL(timeout()), this, SLOT(update()));
}

void GLWidget::clientDraw()
{
	m_solver->getPoints(m_displayVertex);
	//internalTimer()->stop();
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
    glEnableClientState(GL_VERTEX_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, (GLfloat*)m_displayVertex->data());
	glDrawElements(GL_TRIANGLES, numTriangleFaceVertices(), GL_UNSIGNED_INT, (unsigned *)m_triangleIndices->data());

	glDisableClientState(GL_VERTEX_ARRAY);
	
	showRays();
	
	// showEdgeContacts();
	// showAabbs();
	m_solver->setAlpha((float)elapsedTime()/300.f);
	// qDebug()<<"drawn in "<<deltaTime();
	//internalTimer()->start();
}

void GLWidget::showEdgeContacts()
{
    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_LINE);
    
    float * dsyV = (float *)m_displayVertex->data();
	EdgeContact * ec = (EdgeContact *)m_edges->data();
	unsigned ne = m_solver->numLeafNodes();
	unsigned a, b, c, d;
	const float h = 0.2f;
	const unsigned maxI = m_solver->numPoints();
	float * p;
	glBegin(GL_TRIANGLES);
	for(unsigned i=0; i < ne; i++) {
	    EdgeContact & ae = ec[i];
	    a = ae.v[0];
	    b = ae.v[1];
	    c = ae.v[2];
	    d = ae.v[3];
	    
	    if(c < maxI && d < maxI) {
	        p = &dsyV[a * 4];
	        glVertex3f(p[0], p[1] + h, p[2]);
	        p = &dsyV[b * 4];
	        glVertex3f(p[0], p[1] + h, p[2]);
	        p = &dsyV[c * 4];
	        glVertex3f(p[0], p[1] + h, p[2]);
	        
	        p = &dsyV[b * 4];
	        glVertex3f(p[0], p[1] + h, p[2]);
	        p = &dsyV[a * 4];
	        glVertex3f(p[0], p[1] + h, p[2]);
	        p = &dsyV[d * 4];
	        glVertex3f(p[0], p[1] + h, p[2]);
	    }
	    else if(c < maxI) {
	        p = &dsyV[a * 4];
	        glVertex3f(p[0], p[1] + h, p[2]);
	        p = &dsyV[b * 4];
	        glVertex3f(p[0], p[1] + h, p[2]);
	        p = &dsyV[c * 4];
	        glVertex3f(p[0], p[1] + h, p[2]);
	    }
	    else if(d < maxI) {
	        p = &dsyV[a * 4];
	        glVertex3f(p[0], p[1] + h, p[2]);
	        p = &dsyV[b * 4];
	        glVertex3f(p[0], p[1] + h, p[2]);
	        p = &dsyV[d * 4];
	        glVertex3f(p[0], p[1] + h, p[2]);
	    }
	}
	glEnd();
}

inline int isLeafNode(int index) 
{ return (index >> 31 == 0); }

inline int getIndexWithInternalNodeMarkerRemoved(int index) 
{ return index & (~0x80000000); }


void GLWidget::showAabbs()
{
	Aabb ab;
	m_solver->getRootNodeAabb(&ab);
	GeoDrawer * dr = getDrawer();
    BoundingBox bb; 
	bb.setMin(ab.low.x, ab.low.y, ab.low.z);
	bb.setMax(ab.high.x, ab.high.y, ab.high.z);
	glColor3f(0.1f, 0.4f, 0.3f);
    // dr->boundingBox(bb);
	
#ifdef BVHSOLVER_DBG_DRAW
	
#ifdef BVHSOLVER_DBG_DRAW_INTERNALBOX
	Aabb * boxes = m_solver->displayInternalAabbs();
	KeyValuePair * leafHash = m_solver->displayLeafHash();
	Aabb * leaves = m_solver->displayLeafAabbs();
	int * levels = m_solver->displayInternalDistances();
    unsigned ne = m_solver->numInternalNodes();
	int root = m_solver->getRootNodeIndex();
	// qDebug()<<" root at "<< (root & (~0x80000000));
	int2 * internalNodeChildIndices = new int2[ne];
	m_solver->hostInternalNodeChildIndex(internalNodeChildIndices);
	int stack[128];
	stack[0] = root;
	int stackSize = 1;
	int maxStack = 1;
	int touchedLeaf = 0;
	int touchedInternal = 0;
	while(stackSize > 0) {
		int internalOrLeafNodeIndex = stack[ stackSize - 1 ];
		stackSize--;
		
		int isLeaf = isLeafNode(internalOrLeafNodeIndex);	//Internal node if false
		uint bvhNodeIndex = getIndexWithInternalNodeMarkerRemoved(internalOrLeafNodeIndex);
		
		int bvhRigidIndex = (isLeaf) ? leafHash[bvhNodeIndex].value : -1;
		
		Aabb bvhNodeAabb = (isLeaf) ? leaves[bvhRigidIndex] : boxes[bvhNodeIndex];

		{
			if(isLeaf) {
				glColor3f(.5, 0., 0.);
				ab = bvhNodeAabb;
				bb.setMin(ab.low.x, ab.low.y, ab.low.z);
				bb.setMax(ab.high.x, ab.high.y, ab.high.z);
				dr->boundingBox(bb);
				touchedLeaf++;
			}
			else {
				glColor3f(.5, .5, 0.);
				//if(levels[bvhNodeIndex] > m_displayLevel) continue;
				ab = bvhNodeAabb;
				bb.setMin(ab.low.x, ab.low.y, ab.low.z);
				bb.setMax(ab.high.x, ab.high.y, ab.high.z);
				//dr->boundingBox(bb);
				touchedInternal++;
				if(stackSize + 2 > 128)
				{
					//Error
				}
				else
				{
				    stack[ stackSize ] = internalNodeChildIndices[bvhNodeIndex].x;
					stackSize++;
					stack[ stackSize ] = internalNodeChildIndices[bvhNodeIndex].y;
					stackSize++;
					
					if(stackSize > maxStack) maxStack = stackSize;
				}
			}
		}
		
	} 
	
	delete[] internalNodeChildIndices;
	qDebug()<<"max stack "<<maxStack<<" touch leaf "<<touchedLeaf<<" touchedInternal "<<touchedInternal;
	/*
	int ninvalidbox = 0;
    for(unsigned i=0; i < ne; i++) {
		if(levels[i] != m_displayLevel) continue;
        ab = boxes[i];
        
		bb.setMin(ab.low.x, ab.low.y, ab.low.z);
        bb.setMax(ab.high.x, ab.high.y, ab.high.z);
		
		if(!bb.isValid() || bb.area() < 0.1f) {
			// qDebug()<<bb.str().c_str();
			ninvalidbox++;
		}
		
		float redc = ((float)(levels[i] % 22))/22.f;
		
		glColor3f(redc, 1.f - redc, 0.f);
	
        dr->boundingBox(bb);
    }
	if(ninvalidbox > 0) qDebug()<<"n invalid box "<<ninvalidbox;
	*/
#endif	
/*
#ifdef BVHSOLVER_DBG_DRAW_LEAFHASH
	KeyValuePair * leafHash = m_solver->displayLeafHash();
	glColor3f(0.8f, 0.1f, 0.f);
	glBegin(GL_LINES);
	int nzero = 0;
	for(unsigned i=0; i < ne-1; i++) {
		float red = (float)i/(float)ne;
		
		if(leafHash[i].value >= ne) {
			qDebug()<<"invalid hash value "<<leafHash[i].value;
			nzero++;
		}
		
		ab = boxes[leafHash[i].value];
        
		bb.setMin(ab.low.x, ab.low.y, ab.low.z);
        bb.setMax(ab.high.x, ab.high.y, ab.high.z);
		
		glColor3f(red, 1.f - red, 0.f);
		Aabb a0 = boxes[leafHash[i].value];
		glVertex3f(a0.low.x * 0.5f + a0.high.x * 0.5f, a0.low.y * 0.5f + a0.high.y * 0.5f + 0.2f, a0.low.z * 0.5f + a0.high.z * 0.5f);
        
		Aabb a1 = boxes[leafHash[i+1].value];
		glVertex3f(a1.low.x * 0.5f + a1.high.x * 0.5f, a1.low.y * 0.5f + a1.high.y * 0.5f + 0.2f, a1.low.z * 0.5f + a1.high.z * 0.5f);
        
	}
	glEnd();	
	if(nzero > 0) qDebug()<<"n zero code "<<nzero;
#endif
*/
#endif

}

void GLWidget::showRays()
{
	m_solver->getRays(m_displayRays);
	RayInfo * rays = (RayInfo *)m_displayRays->data();
	const unsigned nr = m_solver->numRays();
	glColor3f(0.1f, 0.6f, 0.f);
	glBegin(GL_LINES);
	for(unsigned i=0; i < nr; i++) {
		RayInfo & r = rays[i];
		glVertex3f(r.origin.x, r.origin.y, r.origin.z);
		glVertex3f(r.destiny.x, r.destiny.y, r.destiny.z);
		
		Vector3F a(r.destiny.x - r.origin.x, r.destiny.y - r.origin.y, r.destiny.z - r.origin.z);
		// qDebug()<<" "<<a.length();
	}
	glEnd();
}

void GLWidget::clientSelect(QMouseEvent */*event*/)
{
	setUpdatesEnabled(false);
	
	setUpdatesEnabled(true);
}

void GLWidget::clientDeselect(QMouseEvent */*event*/) 
{
	setUpdatesEnabled(false);
	
	setUpdatesEnabled(true);
}

void GLWidget::clientMouseInput(QMouseEvent */*event*/)
{
	setUpdatesEnabled(false);
	
	setUpdatesEnabled(true);
}

void GLWidget::keyPressEvent(QKeyEvent *event)
{
	switch (event->key()) {
		case Qt::Key_A:
			m_displayLevel++;
			break;
		case Qt::Key_D:
			m_displayLevel--;
			break;
		case Qt::Key_W:
			internalTimer()->stop();
			break;
		case Qt::Key_S:
			internalTimer()->start();
			break;
		default:
			break;
	}
	
	Base3DView::keyPressEvent(event);
}
