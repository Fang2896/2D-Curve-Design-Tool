//
// Created by fangl on 2023/6/12.
//

#include "Algorithms.h"


std::tuple<Eigen::VectorXd, Eigen::VectorXd> Algorithms::convertPoints(const QVector<QVector2D> &points) {
    int n = points.size();
    Eigen::VectorXd xvals(n), yvals(n);
    for(int i = 0; i < n; i++) {
        xvals[i] = points[i].x();
        yvals[i] = points[i].y();
    }

    return std::make_tuple(xvals, yvals);
}

Eigen::VectorXd Algorithms::polynomialFit(const Eigen::VectorXd &xvals, const Eigen::VectorXd &yvals, int order) {
    int n = (int)xvals.size();
    Eigen::MatrixXd A(n, order + 1);

    // Create the Vandermonde matrix
    for (int i = 0; i <= order; ++i)
        A.col(i) = xvals.array().pow(i);

    // Solve the least squares problem
    auto qr = A.householderQr();
    auto result = qr.solve(yvals);

    return result;
}

//std::vector<double> Algorithms::gaussianFit(const std::vector<double> &xvals, const std::vector<double> &yvals, int n) {
    // TODO: 实现高斯基的拟合
//    int m = xvals.size();
//
//    Eigen::MatrixXd A(m, n + 1);
//    A.setConstant(1.0);
//
//    for(int i = 1; i <= n; i++) {
//        for(int j = 0; j < m; j++) {
//            double x = xvals[j];
//            double xi = xvals[i - 1];
//            A(j, i) = std::exp(-(x - xi) * (x - xi) / 2.0);
//        }
//    }
//
//    Eigen::VectorXd b(m);
//    for(int j = 0; j < m; j++) {
//        b(j) = yvals[j];
//    }
//
//    // 用SVD求解
//    Eigen::VectorXd coeffs = A.bdcSvd(Eigen::ComputeThinU | Eigen::ComputeThinV).solve(b);
//
//    std::vector<double> coeffsStd(n + 1);
//    for(int i = 0; i <= n; i++) {
//        coeffsStd[i] = coeffs[i];
//    }
//
//    return coeffsStd;
//}
