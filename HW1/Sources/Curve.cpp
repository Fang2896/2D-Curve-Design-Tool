//
// Created by fangl on 2023/6/8.
//

#include <Eigen/Dense>

#include "Curve.h"


Curve::Curve() {
    curveVBO = 0;
    core = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_3_Core>();
}

Curve::~Curve() {
    core->glDeleteBuffers(1, &curveVBO);
}

void Curve::init(int res, int w, int h) {
    points.clear();
    vertices.clear();
    this->resolution = res;
    this->width = w;
    this->height = h;
    vertices.clear();

    core->glGenBuffers(1, &curveVBO);
    core->glBindBuffer(GL_ARRAY_BUFFER, curveVBO);
    core->glBufferData(GL_ARRAY_BUFFER, sizeof(QVector2D) * vertices.size(),
                       vertices.data(), GL_STATIC_DRAW);
    core->glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Curve::drawCurve() {
    core->glEnableVertexAttribArray(0);
    core->glBindBuffer(GL_ARRAY_BUFFER, curveVBO);

    core->glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE,
                                2 * sizeof(float), (void*) nullptr);
    core->glDrawArrays(GL_LINE_STRIP, 0, vertices.size());

    core->glBindBuffer(GL_ARRAY_BUFFER, 0);
}


/********* Polynomial Fitting **********/
PolynomialFittingCurve::PolynomialFittingCurve() : Curve() {}

// width和height可以确保如果超出了画面的曲线，就不绘制了
void PolynomialFittingCurve::init(int res, int width, int height) {
    Curve::init(res, width, height);
}

void PolynomialFittingCurve::drawCurve() {
    Curve::drawCurve();
}

// 核心函数：根据当前的points，计算曲线，并采样曲线上的点后存入vertices
void PolynomialFittingCurve::updateVertices() {
    vertices.clear();

    if(points.size() < 2) {
        return;
    }

    // 开始拟合
    Eigen::VectorXd  xvals, yvals;
    std::tie(xvals, yvals) = Algorithms::convertPoints(points);

    int order = points.size();
    Eigen::VectorXd coeffs = Algorithms::polynomialFit(xvals, yvals, order);

    // 采样
    double step = (double)width / (double)resolution;
    for(int i = 0; i <= resolution; i++) {
        double x = -(float)width / 2.0f + i * step;
        double y = 0;
        for(int j = 0; j < order; j++) {
            y += coeffs[j] * std::pow(x, j);
        }
        vertices.push_back(QVector2D(x, y));
    }

    core->glBindBuffer(GL_ARRAY_BUFFER, curveVBO);
    core->glBufferData(GL_ARRAY_BUFFER, sizeof(QVector2D) * vertices.size(),
                       vertices.data(), GL_STATIC_DRAW);
    core->glBindBuffer(GL_ARRAY_BUFFER, 0);

}

