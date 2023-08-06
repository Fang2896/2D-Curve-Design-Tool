//
// Created by fangl on 2023/6/8.
//

#include <Eigen/Dense>

#include "Headers/Curve.h"


Curve::Curve() {
    curveVAO = 0;
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

    core->glGenVertexArrays(1, &curveVAO);
    core->glBindVertexArray(curveVAO);

    core->glEnableVertexAttribArray(0);
    core->glBindBuffer(GL_ARRAY_BUFFER, curveVBO);

    core->glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE,
                                2 * sizeof(float), (void*) nullptr);

    core->glBindVertexArray(0);
}

void Curve::drawCurve() {
    core->glBindVertexArray(curveVAO);
    core->glDrawArrays(GL_LINE_STRIP, 0, vertices.size());
    core->glBindVertexArray(0);
}


/********* Polynomial Interpolation **********/
// 核心函数：根据当前的points，计算曲线，并采样曲线上的点后存入vertices
void PolynomialInterpolateCurve::updateVertices() {
    vertices.clear();

    if(points.size() < 2) {
        return;
    }

    // 开始拟合
    Eigen::VectorXd  xvals, yvals;
    std::tie(xvals, yvals) = Algorithms::convertPoints(points);

    Eigen::VectorXd coeffs = Algorithms::polynomialInterpolateCoeff(xvals, yvals);

    // 采样
    double step = (double)width / (double)resolution;
    for(int i = 0; i <= resolution; i++) {
        double x = -(float)width / 2.0f + i * step;
        double y = 0;
        for(int j = 0; j < xvals.size(); j++) {
            y += coeffs[j] * std::pow(x, j);
        }
        vertices.push_back(QVector2D(x, y));
    }

    core->glBindBuffer(GL_ARRAY_BUFFER, curveVBO);
    core->glBufferData(GL_ARRAY_BUFFER, sizeof(QVector2D) * vertices.size(),
                       vertices.data(), GL_STATIC_DRAW);
    core->glBindBuffer(GL_ARRAY_BUFFER, 0);
}


/********* RBF Interpolation **********/
void RBFInterpolateCurve::setSigma(float sigma) {
    this->sigma_ = sigma;
    updateVertices();
}

RBFInterpolateCurve::RBFInterpolateCurve(Kernel_Type kernelType, const float sigma) : Curve(), kernelType_(kernelType), sigma_(sigma) {}

void RBFInterpolateCurve::updateVertices() {
    vertices.clear();

    if(points.size() < 2) {
        return;
    }

    Eigen::VectorXd  xvals, yvals;
    std::tie(xvals, yvals) = Algorithms::convertPoints(points);

    Eigen::VectorXd coeffs = Algorithms::rbfInterpolateCoeff(kernelType_, sigma_, xvals, yvals);

    // 采样
    double step = (double)width / (double)resolution;
    for(int i = 0; i <= resolution; i++) {
        double x = -(float)width / 2.0f + i * step;
        double y = 0;
        for(int j = 0; j < points.size(); j++) {
            if(kernelType_ == Kernel_Type::GAUSSIAN) {
                y += coeffs[j] * Algorithms::computeKernelGaussianValue(x, xvals(j), sigma_);
            }
        }
        vertices.push_back(QVector2D(x, y));
    }

    core->glBindBuffer(GL_ARRAY_BUFFER, curveVBO);
    core->glBufferData(GL_ARRAY_BUFFER, sizeof(QVector2D) * vertices.size(),
                       vertices.data(), GL_STATIC_DRAW);
    core->glBindBuffer(GL_ARRAY_BUFFER, 0);
}


/********* Polynomial Regression **********/
void PolynomialRegressionCurve::setLambda(float lambda) {
    this->lambda_ = lambda;
    updateVertices();
}

void PolynomialRegressionCurve::setOrder(int order) {
    this->order_ = order;
    updateVertices();
}

void PolynomialRegressionCurve::updateVertices() {
    vertices.clear();

    if(points.size() < 2) {
        return;
    }

    Eigen::VectorXd  xvals, yvals;
    std::tie(xvals, yvals) = Algorithms::convertPoints(points);

    Eigen::VectorXd coeffs = Algorithms::polynomialRegressionCoeff(xvals, yvals, order_, lambda_);

    // 采样
    double step = (double)width / (double)resolution;
    for(int i = 0; i <= resolution; i++) {
        double x = -(float)width / 2.0f + i * step;
        double y = 0;
        for(int j = 0; j <= order_; j++) {
                y += coeffs[j] * std::pow(x, j);
        }
        vertices.push_back(QVector2D(x, y));
    }

    core->glBindBuffer(GL_ARRAY_BUFFER, curveVBO);
    core->glBufferData(GL_ARRAY_BUFFER, sizeof(QVector2D) * vertices.size(),
                       vertices.data(), GL_STATIC_DRAW);
    core->glBindBuffer(GL_ARRAY_BUFFER, 0);

}


