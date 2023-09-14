//
// Created by fangl on 2023/8/31.
//

#include "curve_model.h"

void CurveModel::clearData() {
    m_points->clearData();

}

void CurveModel::setResolution(int res) {
    resolution = res;
}

int CurveModel::getPointsSize() {
    return m_points->getPointsSize();
}

const QVector2D* CurveModel::getPointsData() const {
    return m_points->getPointsData().data();
}

const QVector3D* CurveModel::getColorsData() const {
    return m_points->getPointsColorData().data();
}

void CurveModel::setPointPosition(int index, QVector2D position) {
    m_points->setPointPosition(index, position);
}

void CurveModel::setPointColor(int index, QVector3D pointColor) {
    m_points->setPointColor(index, pointColor);
}

void CurveModel::addPoint(QVector2D pos) {
    m_points->addPoint(pos);

    // 是否要更新曲线？这里可以做判断

}

// find the nearest point index among radius
// if not find, return -1
int CurveModel::findNearestPointInRange(QVector2D clickPos, float radius) {
    const QVector<QVector2D> &positions = m_points->getPointsData();

    if(positions.isEmpty()) {
        return -1;
    }

    int nearestPointIndex = -1;
    float minDist = radius;
    for(int i = 0; i < positions.size(); i++) {
        float dist = clickPos.distanceToPoint(positions[i]);
        if(dist < radius && dist < minDist) {
            minDist = dist;
            nearestPointIndex = i;
        }
    }

    return nearestPointIndex;
}


/********* Polynomial Interpolation ***********/
void CurveModel::updatePolyInterCurveData() {
    m_polyInterCurveData.clear();

    if(m_points->getPointsSize() < 2) {
        return;
    }

    Eigen::VectorXd xvals, yvals;
    std::tie(xvals, yvals) = UtilFunc::convertPoints(m_points->getPointsData());
    Eigen::VectorXd coeffs = UtilFunc::polynomialInterpolateCoeff(xvals, yvals);

    // sample points
    double step = (double)width / (double)resolution;
    for(int i = 0; i <= resolution; i++) {
        double x = -(float)width / 2.0f + i * step;
        double y = 0;
        for(int j = 0; j < xvals.size(); j++) {
            y += coeffs[j] * std::pow(x, j);
        }
        m_polyInterCurveData.push_back(QVector2D(x, y));
    }

}

const QVector<QVector2D>& CurveModel::getPolyInterCurveData() const {
    return m_polyInterCurveData;
}

// boolean functions
bool CurveModel::getPolyInterCurveStatus() const {
    return displayPolyInterCurve;
}

void CurveModel::setPolyInterCurveStatus(bool status) {
    displayPolyInterCurve = status;
}

int CurveModel::getPolyInterCurveDataSize() {
    return m_polyInterCurveData.size();
}


/********* RBF Interpolation ***********/
void CurveModel::updateRBFInterCurveData() {
    m_RBFInterCurveData.clear();

    if(m_points->getPointsSize() < 2) {
        return;
    }

    Eigen::VectorXd  xvals, yvals;
    std::tie(xvals, yvals) = UtilFunc::convertPoints(m_points->getPointsData());

    Eigen::VectorXd coeffs = UtilFunc::rbfInterpolateCoeff(m_RBFSigma, xvals, yvals);

    // 采样
    double step = (double)width / (double)resolution;
    for(int i = 0; i <= resolution; i++) {
        double x = -(float)width / 2.0f + i * step;
        double y = 0;
        for(int j = 0; j < m_points->getPointsSize(); j++) {
            // if(kernelType_ == Kernel_Type::GAUSSIAN)
            y += coeffs[j] * UtilFunc::computeKernelGaussianValue(x, xvals(j), m_RBFSigma);
        }
        m_RBFInterCurveData.push_back(QVector2D(x, y));
    }
}

void CurveModel::updateRBFInterSigma(float sigmaValue) {
    m_RBFSigma = sigmaValue;
}

const QVector<QVector2D>& CurveModel::getRBFInterCurveData() const {
    return m_RBFInterCurveData;
}

// boolean functions
bool CurveModel::getRBFInterCurveStatus() const {
    return displayRBFInterCurve;
}

void CurveModel::setRBFInterCurveStatus(bool status) {
    displayRBFInterCurve = status;
}

int CurveModel::getRBFInterCurveDataSize() {
    return m_RBFInterCurveData.size();
}

/********* Polynomial Regression ***********/
void CurveModel::updatePolyRegreCurveData() {
    m_polyRegreCurveData.clear();

    if(m_points->getPointsSize() < 2) {
        return;
    }

    Eigen::VectorXd  xvals, yvals;
    std::tie(xvals, yvals) = UtilFunc::convertPoints(m_points->getPointsData());

    Eigen::VectorXd coeffs = UtilFunc::polynomialRegressionCoeff(xvals, yvals, m_polyRegreOrder, m_polyRegreLambda);

    // 采样
    double step = (double)width / (double)resolution;
    for(int i = 0; i <= resolution; i++) {
        double x = -(float)width / 2.0f + i * step;
        double y = 0;
        for(int j = 0; j <= m_polyRegreOrder; j++) {
            y += coeffs[j] * std::pow(x, j);
        }
        m_polyRegreCurveData.push_back(QVector2D(x, y));
    }
}

void CurveModel::updatePolyRegreOrder(int order) {
    m_polyRegreOrder = order;
}

void CurveModel::updatePolyRegreLambda(float lambda) {
    m_polyRegreLambda = lambda;
}


const QVector<QVector2D>& CurveModel::getPolyRegreCurveData() const {
    return m_polyRegreCurveData;
}

// boolean functions
bool CurveModel::getPolyRegreCurveStatus() const {
    return displayPolyRegreCurve;
}

void CurveModel::setPolyRegreCurveStatus(bool status) {
    displayPolyRegreCurve = status;
}

int CurveModel::getPolyRegreCurveDataSize() {
    return m_polyRegreCurveData.size();
}

/********* Uniform Parameterization ***********/
void CurveModel::updateUniformParamCurveData() {
    m_uniformParamCurveData.clear();
    int num = m_points->getPointsSize();

    if(num < 2) {
        return;
    }

    Eigen::VectorXd  xvals, yvals, tvals;
    std::tie(xvals, yvals) = UtilFunc::convertPoints(m_points->getPointsData());
    tvals = Eigen::VectorXd::LinSpaced(num, 0, 1);

    Eigen::VectorXd xCoeffs = UtilFunc::polynomialInterpolateCoeff(tvals, xvals);
    Eigen::VectorXd yCoeffs = UtilFunc::polynomialInterpolateCoeff(tvals, yvals);

    // 采样
    float startX = xvals(0);
    float endX = xvals(num - 1);
    double step = (double)width / (double)resolution;
    int numSeg = std::floor((endX - startX) / step);

    for(int i = 0; i <= numSeg; i++) {
        double x = 0;
        double y = 0;
        double t = (double)i / numSeg;  // 用于画点
        for(int j = 0; j < num; j++) {
            x += xCoeffs[j] * std::pow(t, j);
            y += yCoeffs[j] * std::pow(t, j);
        }
        m_uniformParamCurveData.push_back(QVector2D(x, y));
    }
}

const QVector<QVector2D>& CurveModel::getUniformParamCurveData() const {
    return m_uniformParamCurveData;
}

// boolean functions
bool CurveModel::getUniformParamCurveStatus() const {
    return displayUniformParamCurve;
}

void CurveModel::setUniformParamCurveStatus(bool status) {
    displayUniformParamCurve = status;
}

int CurveModel::getUniformParamCurveDataSize() {
    return m_uniformParamCurveData.size();
}

/********* Chordal Parameterization ***********/
void CurveModel::updateChordalParamCurveData() {
    m_chordalParamCurveData.clear();
    int num = m_points->getPointsSize();

    if(num < 2) {
        return;
    }

    Eigen::VectorXd  xvals, yvals, tvals(num);
    std::tie(xvals, yvals) = UtilFunc::convertPoints(m_points->getPointsData());

    // 关键的不同就只是t参数的计算罢了
    tvals(0) = 0;
    for(int i = 1; i < num; i++) {
        double dx = xvals(i) - xvals(i - 1);
        double dy = yvals(i) - yvals(i - 1);
        tvals(i) = tvals(i - 1) + std::sqrt(dx*dx + dy*dy);
    }
    tvals /= tvals(num - 1);    // range 0 ~ 1

    Eigen::VectorXd xCoeffs = UtilFunc::polynomialInterpolateCoeff(tvals, xvals);
    Eigen::VectorXd yCoeffs = UtilFunc::polynomialInterpolateCoeff(tvals, yvals);

    // 采样
    float startX = xvals(0);
    float endX = xvals(num - 1);
    double step = (double)width / (double)resolution;
    int numSeg = std::floor((endX - startX) / step);

    for(int i = 0; i <= numSeg; i++) {
        double x = 0;
        double y = 0;
        double t = (double)i / numSeg;  // 用于画点
        for(int j = 0; j < num; j++) {
            x += xCoeffs[j] * std::pow(t, j);
            y += yCoeffs[j] * std::pow(t, j);
        }
        m_chordalParamCurveData.push_back(QVector2D(x, y));
    }

}

const QVector<QVector2D>& CurveModel::getChordalParamCurveData() const {
    return m_chordalParamCurveData;
}

// boolean functions
bool CurveModel::getChordalParamCurveStatus() const {
    return displayChordalParamCurve;
}

void CurveModel::setChordalParamCurveStatus(bool status) {
    displayChordalParamCurve = status;
}

int CurveModel::getChordalParamCurveDataSize() {
    return m_chordalParamCurveData.size();
}

/********* Centrietal Parameterization ***********/
void CurveModel::updateCentrietalParamCurveData() {
    m_centrietalCurveData.clear();
    int num = m_points->getPointsSize();

    if(num < 2) {
        return;
    }

    Eigen::VectorXd  xvals, yvals, tvals(num);
    std::tie(xvals, yvals) = UtilFunc::convertPoints(m_points->getPointsData());

    // 关键的不同就只是t参数的计算罢了
    tvals(0) = 0;
    for(int i = 1; i < num; i++) {
        double dx = xvals(i) - xvals(i - 1);
        double dy = yvals(i) - yvals(i - 1);
        tvals(i) = tvals(i - 1) + std::sqrt(std::sqrt(dx*dx + dy*dy));
    }
    tvals /= tvals(num - 1);    // range 0 ~ 1

    Eigen::VectorXd xCoeffs = UtilFunc::polynomialInterpolateCoeff(tvals, xvals);
    Eigen::VectorXd yCoeffs = UtilFunc::polynomialInterpolateCoeff(tvals, yvals);

    // 采样
    float startX = xvals(0);
    float endX = xvals(num - 1);
    double step = (double)width / (double)resolution;
    int numSeg = std::floor((endX - startX) / step);

    for(int i = 0; i <= numSeg; i++) {
        double x = 0;
        double y = 0;
        double t = (double)i / numSeg;  // 用于画点
        for(int j = 0; j < num; j++) {
            x += xCoeffs[j] * std::pow(t, j);
            y += yCoeffs[j] * std::pow(t, j);
        }
        m_centrietalCurveData.push_back(QVector2D(x, y));
    }
}

const QVector<QVector2D>& CurveModel::getCentrietalParamCurveData() const {
    return m_centrietalCurveData;
}

// boolean functions
bool CurveModel::getCentrietalParamCurveStatus() const {
    return displayCentrietalParamCurve;
}

void CurveModel::setCentrietalParamCurveStatus(bool status) {
    displayCentrietalParamCurve = status;
}

int CurveModel::getCentrietalParamCurveDataSize() {
    return m_centrietalCurveData.size();
}




