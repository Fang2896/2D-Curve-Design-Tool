//
// Created by fangl on 2023/8/31.
//


#include <QVBoxLayout>
#include <QHBoxLayout>

#include "mainwindow.h"
#include "ui/ui_MainWindow.h"

/***** Parameters *****/
const int OGLMANAGER_WIDTH = 800;
const int OGLMANAGER_HEIGHT = 400;


MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent), ui(new Ui::MainWindow), m_model()
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

void MainWindow::configureLayout() {
    m_titleLabel = ui->titleLabel;
    m_curveControlStackedWidget = ui->curveControlStackedWidget;
    m_clearButton = ui->clearButton;

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

    // others ...
}

