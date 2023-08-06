//
// Created by fangl on 2023/6/7.
//

#ifndef HW1_GRID_H
#define HW1_GRID_H

#include <QVector2D>
#include <QOpenGLFunctions_3_3_Core>


class Grid
{
public:
    explicit Grid(int w, int h);
    ~Grid();

    void init();
    void drawGrid();

private:
    int width, height;

    QOpenGLFunctions_3_3_Core *core;
    GLuint gridVAO;
    GLuint gridVBO;

    QVector<QVector2D> data;
    QVector<QVector2D> normalizedData;
};


#endif //HW1_GRID_H
