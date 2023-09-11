//
// Created by fangl on 2023/8/31.
//

#ifndef GL_RENDERER_H
#define GL_RENDERER_H

#include <QMouseEvent>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_3_Core>

#include "curve_model.h"
#include "shader.h"


class GLRenderer : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit GLRenderer(CurveModel &model, QWidget* parent = nullptr,
                        int width = 800, int height = 400);


    void setCurrentCurveType(CurveType type);
    void updateCanvas();


protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;

    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

// variables
private:
    CurveModel &m_model;
    CurveType m_currentCurveType;

    QOpenGLFunctions_4_3_Core *core;

    // VAOs, VBOs
    GLuint pointsVAO;
    GLuint pointsVBO;
    GLuint pointsColorVBO;

    // shaders
    std::unique_ptr<Shader> pointShader;

    // utils variables
    int selectedPointIndex = -1;    // 我发现点的id就是index。草！

// private function
private:
    void initBuffers();
    void initShaders();
    void updateViewProjectMatrix();

    void updatePointsBuffer();
    void updateCurveBuffer();

};


#endif //GL_RENDERER_H
