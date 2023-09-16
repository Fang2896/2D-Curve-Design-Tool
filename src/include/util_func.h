//
// Created by fangl on 2023/9/11.
//

#ifndef UTIL_FUNC_H
#define UTIL_FUNC_H

#include <Eigen/Dense>
#include <QVector2D>
#include <QVector>

class UtilFunc {
   public:
    static std::tuple<Eigen::VectorXd, Eigen::VectorXd> convertPoints(
        const QVector<QVector2D>& points);

    static Eigen::VectorXd polynomialInterpolateCoeff(
        const Eigen::VectorXd& xvals, const Eigen::VectorXd& yvals);

    static Eigen::VectorXd rbfInterpolateCoeff(const float& sigma,
                                               const Eigen::VectorXd& xvals,
                                               const Eigen::VectorXd& yvals);

    static float computeKernelGaussianValue(const float& x, const float& mean,
                                            const float& sigma);

    static Eigen::VectorXd polynomialRegressionCoeff(
        const Eigen::VectorXd& xvals, const Eigen::VectorXd& yvals, int order,
        float lambda);

   private:
    UtilFunc() {}
};

#endif  //UTIL_FUNC_H
