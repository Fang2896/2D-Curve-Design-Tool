//
// Created by fangl on 2023/6/6.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include "Headers/mainwindow.h"
#include "Forms/ui_MainWindow.h"


/***** Parameters *****/
// 必须保证是100的倍数，而且百位数是偶数 （后面来调？）
const int OGLMANAGER_WIDTH = 800;
const int OGLMANAGER_HEIGHT = 400;


MainWindow::MainWindow(QWidget *parent) :
        QWidget(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    /******** Components *********/
    oglmanger = new OGLManager(this, OGLMANAGER_WIDTH, OGLMANAGER_HEIGHT);
//    oglmanger->setFixedWidth(OGLMANAGER_WIDTH);
//    oglmanger->setFixedHeight(OGLMANAGER_HEIGHT);

    ConfigureLayout();

    /******** Slots and Connects *********/
    // PolyInter push button
    connect(polynomialInterpolateButton,
            &QPushButton::toggled,
            this,
            &MainWindow::onPolyInterCurvePushButton);

    // GaussianInter push button
    connect(gaussianInterpolateButton,
            &QPushButton::toggled,
            this,
            &MainWindow::onGaussianInterCurvePushButton);

    // change Gaussian interpolation sigma
    connect(sigmaSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, &MainWindow::onGaussianInterSigmaSpinBox);

    // poly regression push button
    connect(polynomialRegressionButton,
            &QPushButton::toggled,
            this,
            &MainWindow::onPolyRegreCurvePushButton);

    // change poly regression order
    connect(orderSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, &MainWindow::onPolyRegreCurveOrderSpinBox);

    // change poly regression lambda
    connect(lambdaSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, &MainWindow::onPolyRegreCurveLambdaSpinBox);

    // Clear Canvas
    connect(clearCanvasButton,
            &QPushButton::clicked,
            this,
            &MainWindow::onClearCanvasPushButton);

    // Resolution Change
    connect(resSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, &MainWindow::onResolutionSpinBox);

    /******** Set background color *********/
    QPalette pal(this->palette());
    pal.setColor(QPalette::Window, QColor(99, 103, 106));
    this->setAutoFillBackground(true);
    this->setPalette(pal);
}

MainWindow::~MainWindow() {
    delete ui;
    delete oglmanger;
}

void MainWindow::ConfigureLayout() {
    // config
    titleLabel  = ui->label;
    sigmaLabel  = ui->label_2;
    orderLabel   = ui->label_3;
    lambdaLabel = ui->label_4;
    resLabel    = ui->label_5;

    sigmaSpinBox    = ui->doubleSpinBox;
    orderSpinBox     = ui->doubleSpinBox_2;
    lambdaSpinBox   = ui->doubleSpinBox_3;
    resSpinBox      = ui->doubleSpinBox_4;

    polynomialInterpolateButton    = ui->pushButton;
    gaussianInterpolateButton      = ui->pushButton_2;
    polynomialRegressionButton = ui->pushButton_3;
    clearCanvasButton          = ui->pushButton_4;

    /******** Layout *********/
    auto *vLabelLayout = new QVBoxLayout;
    vLabelLayout->addWidget(orderLabel);
    vLabelLayout->addWidget(lambdaLabel);
    vLabelLayout->addWidget(resLabel);

    auto *vSpinBoxLayout = new QVBoxLayout;
    vSpinBoxLayout->addWidget(orderSpinBox);
    vSpinBoxLayout->addWidget(lambdaSpinBox);
    vSpinBoxLayout->addWidget(resSpinBox);

    auto *hParameterLayout = new QHBoxLayout;
    hParameterLayout->addLayout(vLabelLayout);
    hParameterLayout->addLayout(vSpinBoxLayout);

    auto *hSigmaLayout = new QHBoxLayout;
    hSigmaLayout->addWidget(sigmaLabel);
    hSigmaLayout->addWidget(sigmaSpinBox);

    auto *vTotalLayout = new QVBoxLayout;
    titleLabel->setAlignment(Qt::AlignCenter);
    vTotalLayout->addWidget(titleLabel);
    vTotalLayout->addStretch(1);
    vTotalLayout->addWidget(polynomialInterpolateButton);
    vTotalLayout->addWidget(gaussianInterpolateButton);
    vTotalLayout->addLayout(hSigmaLayout);
    vTotalLayout->addStretch(1);
    vTotalLayout->addWidget(polynomialRegressionButton);
    vTotalLayout->addStretch(1);
    vTotalLayout->addLayout(hParameterLayout);
    vTotalLayout->addStretch(5);
    vTotalLayout->addWidget(clearCanvasButton);

    auto *hTotalLayout = new QHBoxLayout;
    hTotalLayout->addWidget(oglmanger, 5);
    hTotalLayout->addLayout(vTotalLayout, 1);

    this->setLayout(hTotalLayout);
}

// Functions
void MainWindow::onPolyInterCurvePushButton() {
    oglmanger->drawPolyInterCurve(polynomialInterpolateButton->isChecked());
}

void MainWindow::onGaussianInterCurvePushButton() {
    oglmanger->drawGaussianInterCurve(gaussianInterpolateButton->isChecked());
}

void MainWindow::onGaussianInterSigmaSpinBox() {
    oglmanger->setGaussianInterSigma((float)sigmaSpinBox->value());
}

void MainWindow::onPolyRegreCurvePushButton() {
    oglmanger->drawPolyRegreCurve(polynomialRegressionButton->isChecked());
}

void MainWindow::onPolyRegreCurveOrderSpinBox() {
    oglmanger->setPolyRegreOrder((int)orderSpinBox->value());
}

void MainWindow::onPolyRegreCurveLambdaSpinBox() {
    oglmanger->setPolyRegreLambda((float)lambdaSpinBox->value());
}

void MainWindow::onClearCanvasPushButton() {
    oglmanger->clearCanvas();
}

void MainWindow::onResolutionSpinBox() {
    oglmanger->resolutionChange((int)resSpinBox->value());
}
