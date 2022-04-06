//===================================================
#include "MainWindow.h"

#include <QAction>
#include <QApplication>
#include <QDebug>
#include <QMenuBar>
#include <QPushButton>
#include <QSettings>
#include <QStyleFactory>

#include "ZDataSourceManager.h"
#include "ZTaskWidget.h"
#include "ZTrainingManager.h"
#include "ZTrainingWidget.h"
#include "ZWorkController.h"
//===================================================
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(qApp->applicationDisplayName());

    zh_createComponents();
    zh_createConnections();

    zh_restoreSettings();

    qApp->setStyle(QStyleFactory::create("Fusion"));
    QPalette p = QPalette(Qt::darkGray);
    p.setColor(QPalette::Window, QColor(30,30,30));
    p.setColor(QPalette::Button, QColor(53,53,53));
    p.setColor(QPalette::Highlight, QColor(60,60,60));
    p.setColor(QPalette::ButtonText, QColor(255,255,255));
    p.setColor(QPalette::WindowText, QColor(255,255,255));
    qApp->setPalette(p);

}
//===================================================
MainWindow::~MainWindow()
{
    // disconnect from database
    zh_saveSettings();
}
//===================================================
void MainWindow::zh_createComponents()
{
    // Menu
    QAction* action = new QAction("Settings");
    menuBar()->addAction(action);

    zv_userButton = new QPushButton;
    menuBar()->setCornerWidget(zv_userButton);

    // Central widget
    zv_stackedWidget = new QStackedWidget;
    setCentralWidget(zv_stackedWidget);

    // create widgets and add  to stacked widget
    zv_taskWidget = new ZTaskWidget;
    zv_trainingWidget = new ZTrainingWidget;

    zv_stackedWidget->addWidget(zv_taskWidget);
    zv_stackedWidget->addWidget(zv_trainingWidget);

    // task model
    zv_dataSourceManager = new ZDataSourceManager(this);
    zv_taskWidget->zp_setTaskModel(zv_dataSourceManager->zp_taskModel());

    // training manager
    zv_trainingManager = new ZTrainingManager(this);
    zv_trainingWidget->zp_connectToTrainingManager(zv_trainingManager);

    zv_workController = new ZWorkController(this);
    zv_workController->zp_setTaskSource(zv_dataSourceManager);
}
//===================================================
void MainWindow::zh_createConnections()
{
    connect(zv_taskWidget, &ZTaskWidget::zg_requestNewTaskCreation,
            zv_dataSourceManager, &ZDataSourceManager::zp_createNewTask);
    connect(zv_taskWidget, &ZTaskWidget::zg_requestTasksRemoving,
            zv_dataSourceManager, &ZDataSourceManager::zp_deleteTasks);

    // work controller connections
    connect(zv_taskWidget, &ZTaskWidget::zg_requestTaskRun,
            zv_workController, &ZWorkController::zp_initTaskStart);
    connect(zv_trainingWidget, &ZTrainingWidget::zg_requestTaskStop,
            zv_workController, &ZWorkController::zp_initTaskStop);

    connect(zv_workController, &ZWorkController::zg_setStackedWidgetIndex,
            zv_stackedWidget, &QStackedWidget::setCurrentIndex);

    connect(zv_workController, &ZWorkController::zg_requestTaskStart,
            zv_trainingManager, &ZTrainingManager::zp_initTaskStart);
    connect(zv_workController, &ZWorkController::zg_requestTaskStop,
            zv_trainingManager, &ZTrainingManager::zp_stopTask);
}
//===================================================
void MainWindow::zh_saveSettings()
{
    QSettings settings;
    settings.setValue("AppGeometry", saveGeometry());
}
//===================================================
void MainWindow::zh_restoreSettings()
{
    QSettings settings;
    restoreGeometry(settings.value("AppGeometry").toByteArray());
}
//===================================================

