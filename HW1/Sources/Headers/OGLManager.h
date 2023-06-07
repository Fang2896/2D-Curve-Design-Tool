//
// Created by fangl on 2023/6/6.
//

#ifndef HW1_OGLMANAGER_H
#define HW1_OGLMANAGER_H

#include <QVector2D>

#include <QDebug>
#include <QOpenGLWidget>
#include <QOpenGLShader>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLFunctions_3_3_Core>

#include <QKeyEvent>
#include <QMouseEvent>


class OGLManager : public QOpenGLWidget {
public:
    explicit OGLManager(QWidget *parent = nullptr, int width = 200, int height = 200);
    ~OGLManager() override = default;

    // data functions
    void clearCanvas();

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    QOpenGLFunctions_3_3_Core *core{};
    QOpenGLShaderProgram *pointShaderProgram;
    QOpenGLShaderProgram *gridShaderProgram;

    QOpenGLVertexArrayObject pointVAO;
    QOpenGLBuffer pointVBO{QOpenGLBuffer::VertexBuffer};

    QVector<QVector2D> points;


};


#endif //HW1_OGLMANAGER_H
