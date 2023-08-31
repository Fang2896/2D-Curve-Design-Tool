# 2D Curve Design Tool

The Qt Curve Designer is a comprehensive tool for curve design and visualization, leveraging the power of OpenGL through Qt's `QOpenGLWidget`. This tool offers a variety of curve design methods, from interpolation to regression, and even advanced techniques like RBF neural networks and Bezier curves.



## Features

1. **Interpolation Methods**:
   * Polynomial Fitting
   * Radial Basis Function (RBF) Fitting
2. **Regression Method**:
   * Polynomial Regression
3. **RBF Neural Network** (TODO)
   * Train and visualize curves based on RBF neural network parameters. (Python interface integration)
4. **Parametric Curves**:
   * Uniform Parameterization
   * Chordal Parameterization
   * Centripetal Parameterization
5. **Bezier Curve Design**:
   * Differentiate between anchor points (points on the curve) and control points (influencing the curvature and continuity around anchor points).