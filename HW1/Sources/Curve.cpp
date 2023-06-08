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
    normalVertices.clear();

    core->glGenBuffers(1, &curveVBO);
    core->glBindBuffer(GL_ARRAY_BUFFER, curveVBO);
    core->glBufferData(GL_ARRAY_BUFFER, sizeof(QVector2D) * normalVertices.size(),
                       normalVertices.data(), GL_STATIC_DRAW);
    core->glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Curve::drawCurve() {
    core->glEnableVertexAttribArray(0);
    core->glBindBuffer(GL_ARRAY_BUFFER, curveVBO);

    core->glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE,
                                2 * sizeof(float), (void*) nullptr);
    core->glDrawArrays(GL_LINE_STRIP, 0, normalVertices.size());

    core->glBindBuffer(GL_ARRAY_BUFFER, 0);
}


/********* Polynomial Fitting **********/
PolynomialFittingCurve::PolynomialFittingCurve(int _order) : Curve() {
    this->order = _order;
}

// 这里的n表示的是多项式最高项的指数
// width和height可以确保如果超出了画面的曲线，就不绘制了
void PolynomialFittingCurve::init(int res, int width, int height) {
    Curve::init(res, width, height);
}

void PolynomialFittingCurve::drawCurve() {
    Curve::drawCurve();
}

// 核心函数：根据当前的points，计算曲线，并采样曲线上的点后存入vertices
void PolynomialFittingCurve::updateVertices() {
    Eigen::MatrixXd X(points.size(), order + 1);
    Eigen::VectorXd Y(points.size());

    for(int i = 0; i < points.size(); i++) {
        for(int j = 0; j < order + 1; j++) {
            X(i, j) = std::pow(points[i].x(), j);
        }
        Y[i] = points[i].y();
    }

    // Solving for polynomial coefficients.
    Eigen::VectorXd coefficients = X.colPivHouseholderQr().solve(Y);
    vertices.clear();

    // Compute the vertices for the curve
    double xMin = -(double)width / 2;
    double xMax = (double)width / 2;
    double dx = (xMax - xMin) / (resolution - 1);

    for(int i = 0; i < points.size(); i++) {
        double x = xMin + i * dx;
        double y = 0;
        for(int j = 0; j < order + 1; j++) {
            y += coefficients[j] * std::pow(x, j);
        }
        vertices.push_back({(float)x, (float)y});
    }

}

