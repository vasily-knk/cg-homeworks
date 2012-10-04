#ifndef QT_VIEWER_H
#define QT_VIEWER_H

#include "obj_model.h"

class qt_viewer : public QGLWidget, protected QGLFunctions
{
    Q_OBJECT

public:
    qt_viewer(QWidget *parent = 0);
    ~qt_viewer();

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

private:
    void loadModel();
    void uploadModel();
    void drawModel();
    
    enum model_loader_state
    {
        STATE_LOADING, STATE_LOADED, STATE_READY
    };

private:
    obj_model model_;
    GLuint verts_id_, indices_id_;
};

#endif // QT_VIEWER_H
