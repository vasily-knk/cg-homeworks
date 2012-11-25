#include "stdafx.h"
#include "qt_viewer.h"

qt_viewer::qt_viewer(QWidget *parent)
    : QGLWidget(parent)
    , model_loaded_(false)
{
}

qt_viewer::~qt_viewer()
{
    glDeleteBuffers(1, &indices_id_);
    glDeleteBuffers(1, &verts_id_);
}

void qt_viewer::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
    
    if (model_loaded_)
        drawModel();
}

void qt_viewer::initializeGL()
{
    glewInit();

    glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
    glClearColor(0.0f, 0.0f, 1.0f, 0.5f);				// Black Background
    glClearDepth(1.0f);									// Depth Buffer Setup
    glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
    glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
    glEnable(GL_CULL_FACE);

    glEnableClientState(GL_VERTEX_ARRAY);						// Enable Vertex Arrays
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    connect(&model_loader_watcher_, SIGNAL(finished()), this, SLOT(modelLoaded()));
    
    model_loader_ = QtConcurrent::run(this, &qt_viewer::loadModel);
    model_loader_watcher_.setFuture(model_loader_);

    setWindowTitle("Loading...");
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
    glTranslatef(0.0f, 0.0f, -10.0f);
}

void qt_viewer::loadModel()
{
    //model_.load_obj("model.obj");
    model_.load_sphere(2, 32);
    //model_.load_triangle();
}

void qt_viewer::drawModel()
{
    glBindBuffer(GL_ARRAY_BUFFER, verts_id_);
    glVertexPointer(3, GL_FLOAT, 0, NULL);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_id_);
    glDrawElements(GL_TRIANGLES, model_.get_indices().size(), GL_UNSIGNED_INT, NULL);
}

void qt_viewer::uploadModel()
{
    glGenBuffers(1, &verts_id_);
    glBindBuffer(GL_ARRAY_BUFFER, verts_id_);
    glBufferData(GL_ARRAY_BUFFER, model_.get_verts().size() * sizeof(vec3_t), &(model_.get_verts()[0]), GL_STATIC_DRAW);

    glGenBuffers(1, &indices_id_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_id_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, model_.get_indices().size() * sizeof(model::index_t), &(model_.get_indices()[0]), GL_STATIC_DRAW);

    setWindowTitle("Done.");
    model_loaded_ = true;
    update();
}

void qt_viewer::modelLoaded()
{
    uploadModel();
}
