#ifndef QT_VIEWER_H
#define QT_VIEWER_H

#include "obj_model.h"

class qt_viewer : public QGLWidget
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
    obj_model model_;
};

#endif // QT_VIEWER_H
