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
    titleLabel      = ui->label;
    titleInterLabel = ui->label_Interpolation;
    titleRegreLabel = ui->label_Regression;
    titleRBFLabel   = ui->label_RBF;
    titleParam      = ui->label_Param;

    sigmaLabel      = ui->label_Sigma;
    orderLabel      = ui->label_Order;
    lambdaLabel     = ui->label_Lambda;
    resLabel        = ui->label_Resolution;

    sigmaSpinBox    = ui->doubleSpinBox;
    orderSpinBox    = ui->doubleSpinBox_2;
    lambdaSpinBox   = ui->doubleSpinBox_3;
    resSpinBox      = ui->doubleSpinBox_4;

    polynomialInterpolateButton     = ui->pushButton_PolyInter;
    gaussianInterpolateButton       = ui->pushButton_RBFInter;
    polynomialRegressionButton      = ui->pushButton_PolyRegre;
    RBFTrainButton                  = ui->pushButton_Train;
    RBFPredictButton                = ui->pushButton_Predict;
    uniformParamButton              = ui->pushButton_UniformParam;
    chordalParamButton              = ui->pushButton_ChordalParam;
    centrietalParamButton           = ui->pushButton_CentrietalParam;

    clearCanvasButton               = ui->pushButton_Clear;

    /******** Layout *********/
    // sigma Line
    auto *hSigmaLineLayout = new QHBoxLayout;
    hSigmaLineLayout->addWidget(sigmaLabel);
    hSigmaLineLayout->addWidget(sigmaSpinBox);

    // order Line
    auto *hOrderLineLayout = new QHBoxLayout;
    hOrderLineLayout->addWidget(orderLabel);
    hOrderLineLayout->addWidget(orderSpinBox);

    // lambda Line
    auto *hLambdaLineLayout = new QHBoxLayout;
    hLambdaLineLayout->addWidget(lambdaLabel);
    hLambdaLineLayout->addWidget(lambdaSpinBox);

    // RBF network Line
    auto *hRBFNetWorkLineLayout = new QHBoxLayout;
    hRBFNetWorkLineLayout->addWidget(RBFTrainButton);
    hRBFNetWorkLineLayout->addWidget(RBFPredictButton);

    // Resolution Line
    auto *hResolutionLineLayout = new QHBoxLayout;
    hResolutionLineLayout->addWidget(resLabel);
    hResolutionLineLayout->addWidget(resSpinBox);

    // Total
    auto *vTotalLayout = new QVBoxLayout;
    titleLabel->setAlignment(Qt::AlignCenter);
    vTotalLayout->addWidget(titleLabel);
    vTotalLayout->addStretch(1);

    vTotalLayout->addWidget(titleInterLabel);
    vTotalLayout->addWidget(polynomialInterpolateButton);
    vTotalLayout->addWidget(gaussianInterpolateButton);
    vTotalLayout->addLayout(hSigmaLineLayout);

    vTotalLayout->addWidget(titleRegreLabel);
    vTotalLayout->addWidget(polynomialRegressionButton);
    vTotalLayout->addLayout(hOrderLineLayout);
    vTotalLayout->addLayout(hLambdaLineLayout);

    vTotalLayout->addWidget(titleRBFLabel);
    vTotalLayout->addLayout(hRBFNetWorkLineLayout);

    vTotalLayout->addWidget(titleParam);
    vTotalLayout->addWidget(uniformParamButton);
    vTotalLayout->addWidget(chordalParamButton);
    vTotalLayout->addWidget(centrietalParamButton);

    vTotalLayout->addStretch(5);
    vTotalLayout->addLayout(hResolutionLineLayout);
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
