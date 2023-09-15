//
// Created by fangl on 2023/8/31.
//


#include <QVBoxLayout>
#include <QHBoxLayout>

#include "mainwindow.h"
#include "ui/ui_MainWindow.h"

/***** Parameters *****/
const int OGLMANAGER_WIDTH = 800;
const int OGLMANAGER_HEIGHT = 600;

const int CURVE_DISPLAY_RANGE_WIDTH = 2000;
const int CURVE_DISPLAY_RANGE_HEIGHT = 2000;


MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent), ui(new Ui::MainWindow), m_model(CURVE_DISPLAY_RANGE_WIDTH, CURVE_DISPLAY_RANGE_HEIGHT)
{
    ui->setupUi(this);

    m_glRenderer = new GLRenderer(m_model, this, OGLMANAGER_WIDTH, OGLMANAGER_HEIGHT);

    configureLayout();
    connectSignal();

    QPalette pal(this->palette());

    pal.setColor(QPalette::Window, QColor(99, 103, 106));
    this->setAutoFillBackground(true);
    this->setPalette(pal);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/********** slot functions *************/
void MainWindow::onClearCanvas() {
    m_model.clearData();
    if(m_model.isBezierMode) {
        m_model.initBezierCurve();
    }

    m_glRenderer->updateCanvas();
}

void MainWindow::updateResolution() {
    auto value = (int)m_resolutionSpinBox->value();
    if(value < 1 || value > 100000) {
        qDebug() << "Resolution Value out of Range!";
        return;
    }

    m_model.setResolution(value);
    m_glRenderer->updateCanvas();   // 这里需要更新buffer数据
}

void MainWindow::switchPage(){
    releaseAllButtons();

    currentStackPage++;
    int nextPageIndex = currentStackPage % 3;
    qDebug() << "Next Page Index: " << nextPageIndex;
    m_curveControlStackedWidget->setCurrentIndex(nextPageIndex);

    // 如果到了Bezier Page，需要进行初始化, 且设置m_model中的模式
    if(nextPageIndex == 2) {
        m_model.isBezierMode = true;
        m_model.initBezierCurve();
        m_displayBezierCurveCheckBox->setCheckState(Qt::Checked);
        m_displayBezierControlLineCheckBox->setCheckState(Qt::Checked);
        m_glRenderer->updateCanvas();
    } else {
        m_model.isBezierMode = false;
        m_model.clearData();
    }

}

void MainWindow::onDisplayPolyInterCurve() {
    m_model.setPolyInterCurveStatus(m_polyInterButton->isChecked());
    qDebug() << "PolyInter Status set: " << m_polyInterButton->isChecked();
    m_glRenderer->update();
}

void MainWindow::onDisplayRBFInterCurve() {
    m_model.setRBFInterCurveStatus(m_RBFInterButton->isChecked());
    qDebug() << "RBFInter Status set: " << m_RBFInterButton->isChecked();
    m_glRenderer->update();
}

void MainWindow::onUpdateRBFInterSigma() {
    auto value = (float)m_RBFSigmaSpinBox->value();
    if(value < 0.01f || value > 500.0f) {
        qDebug() << "RBF Sigma Value out of Range!";
        return;
    }

    m_model.updateRBFInterSigma(value);
    m_glRenderer->updateCanvas();   // 这里需要更新buffer数据
}

void MainWindow::onDisplayPolyRegreCurve() {
    m_model.setPolyRegreCurveStatus(m_polyRegreButton->isChecked());
    qDebug() << "Polynomial Regression Status set: " << m_polyRegreButton->isChecked();
    m_glRenderer->update();
}

void MainWindow::onUpdatePolyRegreOrder() {
    auto value = (int)m_polyRegreOrderSpinBox->value();
    if(value < 1 || value > 500) {
        qDebug() << "Polynomial Regression Order Value out of Range!";
        return;
    }

    m_model.updatePolyRegreOrder(value);
    m_glRenderer->updateCanvas();   // 这里需要更新buffer数据
}

void MainWindow::onUpdatePolyRegreLambda() {
    auto value = (float)m_polyRegreLambdaSpinBox->value();
    if(value < 0.0f || value > 300.0f) {
        qDebug() << "Polynomial Regression Lambda Value out of Range!";
        return;
    }

    m_model.updatePolyRegreLambda(value);
    m_glRenderer->updateCanvas();   // 这里需要更新buffer数据
}

void MainWindow::onDisplayUniformParamCurve() {
    m_model.setUniformParamCurveStatus(m_uniformParamButton->isChecked());
    qDebug() << "Uniform Parametrization Status set: " << m_uniformParamButton->isChecked();
    m_glRenderer->update();
}

void MainWindow::onDisplayChordalParamCurve() {
    m_model.setChordalParamCurveStatus(m_chordalParamButton->isChecked());
    qDebug() << "Chordal Parameterization Status set: " << m_chordalParamButton->isChecked();
    m_glRenderer->update();
}

void MainWindow::onDisplayCentrietalParamCurve() {
    m_model.setCentrietalParamCurveStatus(m_centrietalParamButton->isChecked());
    qDebug() << "Centrietal Parameterization Status set: " << m_centrietalParamButton->isChecked();
    m_glRenderer->update();
}

void MainWindow::onDisplayBezierCurve(int state) {
    if (state == Qt::Checked) {
        m_model.setBezierCurveStatus(true);
    } else if (state == Qt::Unchecked) {
        m_model.setBezierCurveStatus(false);
    }

    m_glRenderer->updateCanvas();
}

void MainWindow::onDisplayBezierControlLine(int state) {
    if (state == Qt::Checked) {
        m_model.setBezierControlLineStatus(true);
    } else if (state == Qt::Unchecked) {
        m_model.setBezierControlLineStatus(false);
    }

    m_glRenderer->updateCanvas();
}

void MainWindow::onChangeBezierContinuity(int index) {
    m_model.setBezierContinuity(index);
    m_glRenderer->updateCanvas();
}

void MainWindow::configureLayout() {
    m_titleLabel = ui->titleLabel;
    m_interPageLabel = ui->interCurveTitle;
    m_paramPageLabel = ui->paramCurveTitle;

    m_RBFSigmaLabel = ui->RBFSigmaLabel;
    m_polyRegreOrderLabel = ui->polyRegreOrderLabel;
    m_polyRegreLambdaLabel = ui->polyRegreLambdaLabel;

    m_bezierTitle = ui->bezierCurveTitle;
    m_bezierContinuityLabel = ui->bezierContinuityLabel;

    m_resolutionLabel = ui->resolutionLabel;

    m_curveControlStackedWidget = ui->curveControlStackedWidget;
    m_curveControlStackedWidget->setCurrentIndex(1);    // 初始页面为1
    m_paramPage = m_curveControlStackedWidget->widget(0);
    m_interpolationPage = m_curveControlStackedWidget->widget(1);
    m_bezierPage = m_curveControlStackedWidget->widget(2);

    m_clearButton = ui->clearButton;
    m_pageSwitchButton = ui->pageSwitchPushButton;

    m_polyInterButton = m_curveControlStackedWidget->findChild<QPushButton*>("polyInterPushButton");
    m_uniformParamButton = m_curveControlStackedWidget->findChild<QPushButton*>("uniformParamPushButton");
    m_chordalParamButton = m_curveControlStackedWidget->findChild<QPushButton*>("chordalParamPushButton");
    m_centrietalParamButton = m_curveControlStackedWidget->findChild<QPushButton*>("centrietalParamPushButton");

    m_RBFInterButton = ui->RBFPushButton;
    m_polyRegreButton = ui->polyRegrePushButton;

    m_RBFSigmaSpinBox = ui->RBFSigmaSpinBox;
    m_polyRegreOrderSpinBox = ui->polyRegreOrderSpinBox;
    m_polyRegreLambdaSpinBox = ui->polyRegreLambdaSpinBox;

    m_displayBezierCurveCheckBox = ui->displayBezierCurveCheckBox;
    m_displayBezierControlLineCheckBox = ui->displayControlLineCheckBox;
    m_bezierContinuityComboBox = ui->BezierContinuityComboBox;

    m_resolutionSpinBox = ui->resolutionSpinBox;

    // layout:
    auto hResolutionLayout = new QHBoxLayout;
    hResolutionLayout->addWidget(m_resolutionLabel);
    hResolutionLayout->addWidget(m_resolutionSpinBox);

    auto hRBFSigmaLayout = new QHBoxLayout;
    hRBFSigmaLayout->addWidget(m_RBFSigmaLabel);
    hRBFSigmaLayout->addWidget(m_RBFSigmaSpinBox);

    auto hPolyRegreOrderLayout = new QHBoxLayout;
    hPolyRegreOrderLayout->addWidget(m_polyRegreOrderLabel);
    hPolyRegreOrderLayout->addWidget(m_polyRegreOrderSpinBox);

    auto hPolyRegreLambdaLayout = new QHBoxLayout;
    hPolyRegreLambdaLayout->addWidget(m_polyRegreLambdaLabel);
    hPolyRegreLambdaLayout->addWidget(m_polyRegreLambdaSpinBox);

    auto hBezierContinuityLayout = new QHBoxLayout;
    hBezierContinuityLayout->addWidget(m_bezierContinuityLabel);
    hBezierContinuityLayout->addWidget(m_bezierContinuityComboBox);

    auto vInterLayout = new QVBoxLayout;
    vInterLayout->addWidget(m_interPageLabel);
    vInterLayout->addWidget(m_polyInterButton);
    vInterLayout->addWidget(m_RBFInterButton);
    vInterLayout->addLayout(hRBFSigmaLayout);
    vInterLayout->addWidget(m_polyRegreButton);
    vInterLayout->addLayout(hPolyRegreOrderLayout);
    vInterLayout->addLayout(hPolyRegreLambdaLayout);
    vInterLayout->addStretch(1);
    m_interpolationPage->setLayout(vInterLayout);

    auto vParamLayout = new QVBoxLayout;
    vParamLayout->addWidget(m_paramPageLabel);
    vParamLayout->addWidget(m_uniformParamButton);
    vParamLayout->addWidget(m_chordalParamButton);
    vParamLayout->addWidget(m_centrietalParamButton);
    vParamLayout->addStretch(1);
    m_paramPage->setLayout(vParamLayout);

    auto vBezierLayout = new QVBoxLayout;
    vBezierLayout->addWidget(m_bezierTitle);
    vBezierLayout->addLayout(hBezierContinuityLayout);
    vBezierLayout->addWidget(m_displayBezierCurveCheckBox);
    vBezierLayout->addWidget(m_displayBezierControlLineCheckBox);
    vBezierLayout->addStretch(1);
    m_bezierPage->setLayout(vBezierLayout);

    auto vDashLayout = new QVBoxLayout;
    vDashLayout->addWidget(m_titleLabel);
    vDashLayout->addWidget(m_curveControlStackedWidget);
    vDashLayout->addWidget(m_pageSwitchButton);
    vDashLayout->addLayout(hResolutionLayout);
    vDashLayout->addStretch(1);
    vDashLayout->addWidget(m_clearButton);

    auto mainLayout = new QHBoxLayout;
    mainLayout->addWidget(m_glRenderer, 5);
    mainLayout->addLayout(vDashLayout, 1);

    this->setLayout(mainLayout);
}

void MainWindow::connectSignal() {
    // clear
    connect(m_clearButton,
            &QPushButton::clicked,
            this,
            &MainWindow::onClearCanvas);

    connect(m_resolutionSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, &MainWindow::updateResolution);

    // QStackedWidget Switch and Clear Data
    connect(m_curveControlStackedWidget,
            &QStackedWidget::currentChanged,
            this,
            &MainWindow::onClearCanvas);

    connect(m_pageSwitchButton,
            &QPushButton::clicked,
            this,
            &MainWindow::switchPage);

    connect(m_polyInterButton,
            &QPushButton::toggled,
            this,
            &MainWindow::onDisplayPolyInterCurve);

    connect(m_RBFInterButton,
            &QPushButton::toggled,
            this,
            &MainWindow::onDisplayRBFInterCurve);

    // change RBF interpolation sigma
    connect(m_RBFSigmaSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, &MainWindow::onUpdateRBFInterSigma);

    connect(m_polyRegreButton,
            &QPushButton::toggled,
            this,
            &MainWindow::onDisplayPolyRegreCurve);

    // Polynomial Regression
    connect(m_polyRegreOrderSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, &MainWindow::onUpdatePolyRegreOrder);

    connect(m_polyRegreLambdaSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, &MainWindow::onUpdatePolyRegreLambda);

    // Parameterization Curve
    connect(m_uniformParamButton,
            &QPushButton::toggled,
            this,
            &MainWindow::onDisplayUniformParamCurve);

    connect(m_chordalParamButton,
            &QPushButton::toggled,
            this,
            &MainWindow::onDisplayChordalParamCurve);

    connect(m_centrietalParamButton,
            &QPushButton::toggled,
            this,
            &MainWindow::onDisplayCentrietalParamCurve);

    connect(m_displayBezierCurveCheckBox,
            &QCheckBox::stateChanged,
            this,
            &MainWindow::onDisplayBezierCurve);

    connect(m_displayBezierControlLineCheckBox,
            &QCheckBox::stateChanged,
            this,
            &MainWindow::onDisplayBezierControlLine);

    connect(m_bezierContinuityComboBox,
            QOverload<int>::of(&QComboBox::currentIndexChanged),
            this,
            &MainWindow::onChangeBezierContinuity);


    // others ...
}

void MainWindow::releaseAllButtons() {
    qDebug() << "Release All Buttons!";
    m_polyInterButton->setChecked(false);
    m_RBFInterButton->setChecked(false);
    m_polyRegreButton->setChecked(false);

    m_uniformParamButton->setChecked(false);
    m_chordalParamButton->setChecked(false);
    m_centrietalParamButton->setChecked(false);

    m_displayBezierCurveCheckBox->setCheckState(Qt::Unchecked);
    m_displayBezierControlLineCheckBox->setCheckState(Qt::Unchecked);
}

