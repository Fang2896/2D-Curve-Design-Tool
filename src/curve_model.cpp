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
    if(isBezierMode) {
        QVector2D deltaPos = position - m_points->getIndexPosition(index);

        if(index % 3 == 0) {    // anchor point
            if(index == 0) {
                m_points->movePointDeltaPosition(index + 1, deltaPos);
            } else if(index == m_points->getPointsSize() - 1) {
                m_points->movePointDeltaPosition(index - 1, deltaPos);
            } else {
                m_points->movePointDeltaPosition(index + 1, deltaPos);
                m_points->movePointDeltaPosition(index - 1, deltaPos);
            }
        } else if (index != 1 && index != m_points->getPointsSize() - 2){                // control point
            // TODO: 根据continuity决定move行为， 目前先G0连续吧
            int neighborIndex = index % 3 == 1 ? index - 2 : index + 2;
            m_points->movePointDeltaPosition(neighborIndex, -1.0f * deltaPos);
            m_points->setPointPosition(index, position);
        }
    }

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

/********* Bezier Curve ***********/
void CurveModel::initBezierCurve() {
    clearData();

    QVector2D center = QVector2D(0.0f, 0.0f);
    // 用m_points, 同时存储anchor和control points
    m_points->addPoint(center + QVector2D(-100.0f, 0.0f));   // anchor 0
    m_points->addPoint(center + QVector2D(-50.0f, 50.0f));  // control 1
    m_points->addPoint(center + QVector2D(50.0f, -50.0f));   // control 2
    m_points->addPoint(center + QVector2D(100.0f, 0.0f));   // anchor 3
}

void CurveModel::addBezierSegment(QVector2D anchorPos) {
    QVector2D last1 = m_points->getIndexPosition(-1);
    QVector2D last2 = m_points->getIndexPosition(-2);

    QVector2D newControlPoint0 = 2 * last1 - last2;
    QVector2D newControlPoint1 = (anchorPos + newControlPoint0) / 2.0f;

    m_points->addPoint(newControlPoint0);
    m_points->addPoint(newControlPoint1);
    m_points->addPoint(anchorPos);
}

QVector<QVector2D> CurveModel::getPointsInSegment(int i) {
    const QVector<QVector2D> data = m_points->getPointsData();
    return QVector<QVector2D>{data[i*3],    // anchor 0
                              data[i*3+1],  // control 1
                              data[i*3+2],  // control 2
                              data[i*3+3]}; // anchor 3
}

int CurveModel::getNumOfSegment() {
    return (m_points->getPointsSize() - 4) / 3 + 1;
}

void CurveModel::updateBezierData() {
    m_bezierCurveData.clear();
    m_controlLineData.clear();

    // 暂时不考虑增量型增加点， 因为移动的话，考虑起来很麻烦
    int segNum = getNumOfSegment();
    float step = 5.0f / (float)resolution;

    for(int i = 0; i < segNum; i++) {
        QVector<QVector2D> segPoints = getPointsInSegment(i);
        QVector2D p0 = segPoints[0];
        QVector2D p1 = segPoints[1];
        QVector2D p2 = segPoints[2];
        QVector2D p3 = segPoints[3];

        // 曲线部分
        for(float t = 0; t <= 1; t += step) {
            float u = 1 - t;
            float tt = t * t;
            float uu = u * u;
            float uuu = uu * u;
            float ttt = tt * t;

            QVector2D p = uuu * p0; // (1-t)^3 * P0
            p += 3 * uu * t * p1; // 3(1-t)^2 * t * P1
            p += 3 * u * tt * p2; // 3(1-t) * t^2 * P2
            p += ttt * p3; // t^3 * P3

            m_bezierCurveData.append(p);
        }

        // 控制线部分, 注意这里要两个两个点画
        m_controlLineData.append(p0);
        m_controlLineData.append(p1);
        m_controlLineData.append(p2);
        m_controlLineData.append(p3);
    }
}


const QVector<QVector2D>& CurveModel::getBezierCurveData() const {
    return m_bezierCurveData;
}

const QVector<QVector2D>& CurveModel::getBezierControlLineData() const {
    return m_controlLineData;
}

bool CurveModel::getBezierCurveStatus() const {
    return displayBezierCurve;
}

bool CurveModel::getBezierControlLineStatus() const {
    return displayBezierControlLine;
}

void CurveModel::setBezierCurveStatus(bool status) {
    displayBezierCurve = status;
}

void CurveModel::setBezierControlLineStatus(bool status) {
    displayBezierControlLine = status;
}

int CurveModel::getBezierCurveDataSize() {
    return m_bezierCurveData.size();
}

int CurveModel::getBezierControlLineDataSize() {
    return m_controlLineData.size();
}


