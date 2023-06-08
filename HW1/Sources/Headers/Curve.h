//
// Created by fangl on 2023/6/8.
//

#ifndef HW1_CURVE_H
#define HW1_CURVE_H

#include <QVector>
#include <QVector2D>
#include <QOpenGLFunctions_3_3_Core>


class Curve
{
public:
    Curve();
    ~Curve();

    void setInputPoints(const QVector<QVector2D>& data) {
        this->points = data;
        updateVertices();
    }

    void addInputPoints(const QVector2D& point) {
        this->points.push_back(point);
        updateVertices();
    }

    virtual void init(int res, int width, int height);
    virtual void drawCurve();

protected:
    QOpenGLFunctions_3_3_Core *core;
    GLuint curveVBO;

    QVector<QVector2D> points;      // 基点
    QVector<QVector2D> vertices;    // 曲线的顶点
    QVector<QVector2D> normalVertices;  // -1 ~ 1

    int resolution{};
    int width{};
    int height{};

    virtual void updateVertices() = 0;

};

class PolynomialFittingCurve : public Curve {
public:
    explicit PolynomialFittingCurve(int order);

    void init(int res, int width, int height) override;
    void drawCurve() override;

protected:
    void updateVertices() override;

private:
    // 多项式最高阶阶数
    int order = 5;

};


#endif //HW1_CURVE_H
