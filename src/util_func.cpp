//
// Created by fangl on 2023/9/11.
//

#include "util_func.h"

std::tuple<Eigen::VectorXd, Eigen::VectorXd> UtilFunc::convertPoints(
    const QVector<QVector2D>& points) {
    int n = points.size();
    Eigen::VectorXd xvals(n), yvals(n);
    for (int i = 0; i < n; i++) {
        xvals[i] = points[i].x();
        yvals[i] = points[i].y();
    }

    return std::make_tuple(xvals, yvals);
}

Eigen::VectorXd UtilFunc::polynomialInterpolateCoeff(
    const Eigen::VectorXd& xvals, const Eigen::VectorXd& yvals) {
    int n = (int)xvals.size();
    Eigen::MatrixXd A(n, n);

    // Create the Vandermonde matrix
    for (int i = 0; i < n; ++i)
        A.col(i) = xvals.array().pow(i);

    // Solve the least squares problem
    return A.colPivHouseholderQr().solve(yvals);
}

Eigen::VectorXd UtilFunc::rbfInterpolateCoeff(const float& sigma,
                                              const Eigen::VectorXd& xvals,
                                              const Eigen::VectorXd& yvals) {
    int n = (int)xvals.size();
    Eigen::MatrixXd Phi(n, n);
    Phi.setZero();

    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            // if(kernelType == Kernel_Type::GAUSSIAN)
            Phi(i, j) = computeKernelGaussianValue(xvals(i), xvals(j), sigma);

            Phi(j, i) = Phi(i, j);
        }
    }

    // Eigen::VectorXd result = Phi.lu().solve(yvals);
    auto result =
        Phi.jacobiSvd(Eigen::ComputeThinU | Eigen::ComputeThinV).solve(yvals);
    return result;
}

// kernel function
float UtilFunc::computeKernelGaussianValue(const float& x, const float& mean,
                                           const float& sigma) {
    float diff = x - mean;
    float exponent = -(diff * diff) / (2 * sigma * sigma);

    return std::exp(exponent);
}

Eigen::VectorXd UtilFunc::polynomialRegressionCoeff(
    const Eigen::VectorXd& xvals, const Eigen::VectorXd& yvals, int order,
    float lambda) {
    int n = (int)xvals.size();
    Eigen::MatrixXd X(n, order + 1);

    for (int i = 0; i <= order; i++) {
        X.col(i) = xvals.array().pow(i);
    }

    Eigen::MatrixXd I = Eigen::MatrixXd::Identity(order + 1, order + 1);
    Eigen::VectorXd result =
        (X.transpose() * X + lambda * I).ldlt().solve(X.transpose() * yvals);

    return result;
    // return X.jacobiSvd(Eigen::ComputeThinU | Eigen::ComputeThinV).solve(yvals);
}
