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
    m_glRenderer->updateCanvas();
}

void MainWindow::onDisplayPolyInterCurve() {
    m_model.setPolyInterCurveStatus(m_polyInterButton->isChecked());
    qDebug() << "PolyInter Status set: " << m_polyInterButton->isChecked();
    m_glRenderer->update();
}

void MainWindow::configureLayout() {
    m_titleLabel = ui->titleLabel;
    m_curveControlStackedWidget = ui->curveControlStackedWidget;
    m_clearButton = ui->clearButton;
    m_polyInterButton = m_curveControlStackedWidget->findChild<QPushButton*>("polyInterPushButton");

    // layout:
    auto vDashLayout = new QVBoxLayout;
    vDashLayout->addWidget(m_titleLabel);
    vDashLayout->addWidget(m_curveControlStackedWidget);
    vDashLayout->addWidget(m_clearButton);

    auto mainLayout = new QHBoxLayout;
    mainLayout->addWidget(m_glRenderer, 5);
    mainLayout->addLayout(vDashLayout, 1);

    this->setLayout(mainLayout);
}

void MainWindow::connectSignal() {
    connect(m_clearButton,
            &QPushButton::clicked,
            this,
            &MainWindow::onClearCanvas);

    connect(m_polyInterButton,
            &QPushButton::toggled,
            this,
            &MainWindow::onDisplayPolyInterCurve);

    // others ...
}

