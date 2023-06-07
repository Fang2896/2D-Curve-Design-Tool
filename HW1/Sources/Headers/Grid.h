//
// Created by fangl on 2023/6/7.
//

#ifndef HW1_GRID_H
#define HW1_GRID_H

#include <QVector>
#include <QVector2D>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions_3_3_Core>


class Grid
{
public:
    explicit Grid(int glWidth, int glHeight);
    ~Grid() = default;

    void init();
    void drawGrid();

private:
    int xRange; // [-xRange, xRange]
    int yRange; // [-yRange, yRange]

    QOpenGLFunctions_3_3_Core *core;
    QOpenGLBuffer gridVBO{QOpenGLBuffer::VertexBuffer};

    QVector<QVector2D> gridPoints;
    QVector<QVector2D> gridNormalPoints;

};


#endif //HW1_GRID_H
