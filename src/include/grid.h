//
// Created by fangl on 2023/9/11.
//

#ifndef GRID_H
#define GRID_H


#include <QVector2D>
#include <QOpenGLFunctions_4_3_Core>


class Grid
{
public:
    explicit Grid(int w, int h);
    ~Grid();

    void init();
    void drawGrid();

private:
    int width, height;

    QOpenGLFunctions_4_3_Core *core;
    GLuint gridVAO;
    GLuint gridVBO;

    QVector<QVector2D> data;
    // QVector<QVector2D> normalizedData;
};


#endif //GRID_H
