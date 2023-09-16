//
// Created by fangl on 2023/8/31.
//

#ifndef CURVE_MODEL_H
#define CURVE_MODEL_H

#include <QVector2D>
#include <QVector>

#include <Eigen/Dense>
#include <memory>

#include "point.h"
#include "util_func.h"

//
//enum class CurveType {
//    fittingCurve,
//    parameterizationCurve,
//    bezierCurve
//};
//

class CurveModel {
   public:
    CurveModel(int w, int h) : width(w), height(h) {
        m_points = std::make_unique<Points>();
        resolution = 5000;
    }

    // public variables
    bool isBezierMode = false;
    int bezierContinuity = 2;

    void clearData();
    void setResolution(int res);

    int getPointsSize();
    const QVector2D* getPointsData() const;
    const QVector3D* getColorsData() const;

    void setPointPosition(int index, QVector2D position);
    void setPointColor(int index, QVector3D pointColor);

    void addPoint(QVector2D pos);
    int findNearestPointInRange(QVector2D clickPos, float radius);

    // curve data getter and setter and updater
    // 1: poly inter
    void updatePolyInterCurveData();
    const QVector<QVector2D>& getPolyInterCurveData() const;
    bool getPolyInterCurveStatus() const;
    void setPolyInterCurveStatus(bool status);
    int getPolyInterCurveDataSize();

    // 2: RBF inter
    void updateRBFInterCurveData();
    void updateRBFInterSigma(float sigmaValue);
    const QVector<QVector2D>& getRBFInterCurveData() const;
    bool getRBFInterCurveStatus() const;
    void setRBFInterCurveStatus(bool status);
    int getRBFInterCurveDataSize();

    // 3: poly regre
    void updatePolyRegreCurveData();
    void updatePolyRegreOrder(int order);
    void updatePolyRegreLambda(float lambda);
    const QVector<QVector2D>& getPolyRegreCurveData() const;
    bool getPolyRegreCurveStatus() const;
    void setPolyRegreCurveStatus(bool status);
    int getPolyRegreCurveDataSize();

    // 4: uniform param
    void updateUniformParamCurveData();
    const QVector<QVector2D>& getUniformParamCurveData() const;
    bool getUniformParamCurveStatus() const;
    void setUniformParamCurveStatus(bool status);
    int getUniformParamCurveDataSize();

    // 5: chordal param
    void updateChordalParamCurveData();
    const QVector<QVector2D>& getChordalParamCurveData() const;
    bool getChordalParamCurveStatus() const;
    void setChordalParamCurveStatus(bool status);
    int getChordalParamCurveDataSize();

    // 6: centrietal param
    void updateCentrietalParamCurveData();
    const QVector<QVector2D>& getCentrietalParamCurveData() const;
    bool getCentrietalParamCurveStatus() const;
    void setCentrietalParamCurveStatus(bool status);
    int getCentrietalParamCurveDataSize();

    // 7: bezier curve
    void initBezierCurve();
    void addBezierSegment(QVector2D anchorPos);
    QVector<QVector2D> getPointsInSegment(int i);
    int getNumOfSegment();

    void updateBezierData();

    const QVector<QVector2D>& getBezierCurveData() const;
    const QVector<QVector2D>& getBezierControlLineData() const;

    bool getBezierCurveStatus() const;
    bool getBezierControlLineStatus() const;

    void setBezierCurveStatus(bool status);
    void setBezierControlLineStatus(bool status);

    int getBezierCurveDataSize();
    int getBezierControlLineDataSize();
    void setBezierContinuity(int index);

   private:
    // QVector<Point> m_points;
    std::unique_ptr<Points> m_points;

    QVector<QVector2D> m_polyInterCurveData;

    QVector<QVector2D> m_RBFInterCurveData;
    float m_RBFSigma = 50.0f;

    QVector<QVector2D> m_polyRegreCurveData;
    int m_polyRegreOrder = 3;
    float m_polyRegreLambda = 0.0f;

    QVector<QVector2D> m_uniformParamCurveData;
    QVector<QVector2D> m_chordalParamCurveData;
    QVector<QVector2D> m_centrietalCurveData;

    // 曲线采样点
    QVector<QVector2D> m_bezierCurveData;
    // 控制线
    QVector<QVector2D> m_controlLineData;

    int width;
    int height;
    int resolution;

    // display curve booleans
    bool displayPolyInterCurve = false;
    bool displayRBFInterCurve = false;
    bool displayPolyRegreCurve = false;
    bool displayUniformParamCurve = false;
    bool displayChordalParamCurve = false;
    bool displayCentrietalParamCurve = false;
    bool displayBezierCurve = false;
    bool displayBezierControlLine = false;
};

#endif  //CURVE_MODEL_H
