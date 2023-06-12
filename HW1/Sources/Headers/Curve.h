//
// Created by fangl on 2023/6/8.
//

#ifndef HW1_CURVE_H
#define HW1_CURVE_H

#include <QDebug>
#include <QVector>
#include <QVector2D>
#include <QOpenGLFunctions_3_3_Core>

#include "Algorithms.h"


class Curve
{
public:
    Curve();
    ~Curve();

    void setInputPoints(const QVector<QVector2D>& data) {
        this->points = data;
        updateVertices();
    }

    void addInputPoints(QVector2D point) {
        this->points.push_back(point);
        updateVertices();
    }

    void clearData() {
        points.clear();
        vertices.clear();
    }

    virtual void init(int res, int width, int height);
    virtual void drawCurve();

protected:
    QOpenGLFunctions_3_3_Core *core;
    GLuint curveVBO;

    QVector<QVector2D> points;      // 基点
    QVector<QVector2D> vertices;    // 要显示的曲线的顶点

    int resolution{};
    int width{};
    int height{};

    // 根据point来更新vertices的函数
    virtual void updateVertices() = 0;

};

class PolynomialFittingCurve : public Curve {
public:
    explicit PolynomialFittingCurve();

    void init(int res, int width, int height) override;
    void drawCurve() override;

protected:
    void updateVertices() override;

};


#endif //HW1_CURVE_H
