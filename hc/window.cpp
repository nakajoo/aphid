/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial Usage
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtGui>

#include "glwidget.h"
#include "ControlWidget.h"
#include "window.h"

//! [0]
Window::Window()
{
    glWidget = new GLWidget;
	m_control = new ControlWidget;
	
	QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(m_control);
    mainLayout->addWidget(glWidget);
	
	glWidget->setControlGraph(m_control->getControlGraph());

	QWidget *mainWidget = new QWidget;
	mainWidget->setLayout(mainLayout);
	setCentralWidget(mainWidget);
    setWindowTitle(tr("Partial Blend Shape"));
	
	connect(m_control, SIGNAL(handleChanged(unsigned)), glWidget, SLOT(onHandleChanged(unsigned)));
}
//! [1]

void Window::keyPressEvent(QKeyEvent *e)
{
	if (e->key() == Qt::Key_Escape)
        close();
	else if(e->key() == Qt::Key_A) {
		qDebug() << "anchor selected as one";
		glWidget->anchorSelected(1.f);
	}
	else if(e->key() == Qt::Key_Z) {
		qDebug() << "anchor selected as zero";
		glWidget->anchorSelected(0.f);
	}
	else if(e->key() == Qt::Key_D) {
		qDebug() << "calculate coordinate";
		glWidget->startDeform();
	}
    /*
	else if(e->key() == Qt::Key_R) {
		qDebug() << "rotate mode";
		glWidget->getSolver()->setInteractMode(DynamicsSolver::RotateJoint);
	}*/
	QWidget::keyPressEvent(e);
}
