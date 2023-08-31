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

    void setResolution(int res) {
        this->resolution = res;
        updateVertices();
    }

    void setWidgetSize(int w, int h) {
        this->width = w;
        this->height = h;
        updateVertices();
    }

    virtual void addInputPoints(QVector2D point) {
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
    GLuint curveVAO;
    GLuint curveVBO;

    QVector<QVector2D> points;      // 基点
    QVector<QVector2D> vertices;    // 要显示的曲线的顶点

    int resolution{};
    int width{};
    int height{};

    // 根据point来更新vertices的函数
    virtual void updateVertices() = 0;

};

class PolynomialInterpolateCurve : public Curve {
public:
    PolynomialInterpolateCurve() : Curve() {}

protected:
    void updateVertices() override;

};

class RBFInterpolateCurve : public Curve {
public:
    explicit RBFInterpolateCurve(Kernel_Type kernelType, float sigma = 100);
    void setSigma(float sigma);

protected:
    void updateVertices() override;

private:
    Kernel_Type kernelType_;
    float sigma_;
};

class PolynomialRegressionCurve : public Curve {
public:
    PolynomialRegressionCurve() : Curve(), order_(3), lambda_(0) {}
    void setLambda(float lambda);
    void setOrder(int order);

protected:
    void updateVertices() override;

private:
    int order_;
    float lambda_;
};

class RBFNNPredictCurve : public Curve {
public:
    RBFNNPredictCurve() : Curve() {}

protected:
    // update就是重新训练 + 重新predict
    void updateVertices() override;

};

// 3 parameters methods

class UniformParamCurve : public Curve {
public:
    UniformParamCurve() : Curve() {}

protected:
    void updateVertices() override;

};

class ChordalParamCurve : public Curve {
public:
    ChordalParamCurve() : Curve() {}

protected:
    void updateVertices() override;

};

class CentrietalParamCurve : public Curve {
public:
    CentrietalParamCurve() : Curve() {}

protected:
    void updateVertices() override;

};


#endif //HW1_CURVE_H
