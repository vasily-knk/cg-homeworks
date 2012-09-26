#include "stdafx.h"
#include "qt_viewer.h"

qt_viewer::qt_viewer(QWidget *parent)
    : QGLWidget(parent)
    , model_("model.obj")
{
}

qt_viewer::~qt_viewer()
{

}

void qt_viewer::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
}

void qt_viewer::initializeGL()
{
    glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
    glClearDepth(1.0f);									// Depth Buffer Setup
    glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
    glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
}

void qt_viewer::resizeGL(const int width, const int height)
{
    glViewport(0, 0, width, height);				    // Reset The Current Viewport

    glMatrixMode(GL_PROJECTION);					    // Select The Projection Matrix
    glLoadIdentity();									// Reset The Projection Matrix

    // Calculate The Aspect Ratio Of The Window
    gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
    glLoadIdentity();									// Reset The Modelview Matrix}
}
