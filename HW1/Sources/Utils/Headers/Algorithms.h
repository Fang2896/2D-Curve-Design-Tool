//
// Created by fangl on 2023/6/12.
//

#ifndef HW1_ALGORITHMS_H
#define HW1_ALGORITHMS_H

#include <Eigen/Dense>
#include <QVector>
#include <QVector2D>

enum class Kernel_Type {
    GAUSSIAN,
    LINEAR
};



class Algorithms
{
public:
    static std::tuple<Eigen::VectorXd, Eigen::VectorXd>
            convertPoints(const QVector<QVector2D> &points);

    static Eigen::VectorXd polynomialInterpolateCoeff(const Eigen::VectorXd &xvals,
                                         const Eigen::VectorXd &yvals);

    static Eigen::VectorXd rbfInterpolateCoeff(Kernel_Type kernelType,
                                               const float &sigma,
                                               const Eigen::VectorXd &xvals,
                                               const Eigen::VectorXd &yvals);

    static float computeKernelGaussianValue(const float &x, const float &mean, const float &sigma);

    static Eigen::VectorXd polynomialRegressionCoeff(const Eigen::VectorXd &xvals,
                                                     const Eigen::VectorXd &yvals,
                                                     int order, float lambda);

private:
    Algorithms() {}

};


#endif //HW1_ALGORITHMS_H
