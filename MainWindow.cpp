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
#include "ZSettingsDialog.h"
#include "ZStatisticsWidget.h"
#include "ZTaskStatisticsManager.h"
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

    qApp->setStyle(QStyleFactory::create("Fusion"));
    QPalette p = QPalette(Qt::darkGray);
    p.setColor(QPalette::Window, QColor(30,30,30));
    p.setColor(QPalette::Button, QColor(53,53,53));
    p.setColor(QPalette::Highlight, QColor(60,60,60));
    p.setColor(QPalette::ButtonText, QColor(255,255,255));
    p.setColor(QPalette::WindowText, QColor(255,255,255));
    qApp->setPalette(p);

    zh_restoreSettings();
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
//    QMenu* mainMenu = new QMenu();
//    mainMenu->setToolTip(tr("Main menu"));
//    mainMenu->setIcon(QIcon(":images/menu-512.png"));
//    menuBar()->addMenu(mainMenu);

    zv_settingsAction = new QAction;
    //zv_settingsAction->setToolTip(tr("Settings"));
    zv_settingsAction->setIcon(QIcon(":images/settings-01.png"));
    menuBar()->addAction(zv_settingsAction);

//    zv_userButton = new QPushButton;
//    menuBar()->setCornerWidget(zv_userButton);

    // Central widget
    zv_stackedWidget = new QStackedWidget;
    setCentralWidget(zv_stackedWidget);

    // create widgets and add  to stacked widget
    zv_taskWidget = new ZTaskWidget;
    zv_trainingWidget = new ZTrainingWidget;
    zv_statisticsWidget = new ZStatisticsWidget;

    zv_stackedWidget->addWidget(zv_taskWidget);
    zv_stackedWidget->addWidget(zv_trainingWidget);
    zv_stackedWidget->addWidget(zv_statisticsWidget);

    // task model
    zv_dataSourceManager = new ZDataSourceManager(this);
    zv_taskWidget->zp_setTaskModel(zv_dataSourceManager->zp_taskModel());

    // training manager
    zv_trainingManager = new ZTrainingManager(this);
    zv_trainingWidget->zp_connectToTrainingManager(zv_trainingManager);

    zv_workController = new ZWorkController(this);
    zv_workController->zp_setTaskSource(zv_dataSourceManager);

    // task Statistics manager
    zv_taskStatisticsManager = new ZTaskStatisticsManager(this);
    zv_taskStatisticsManager->zp_connectToTrainingManager(zv_trainingManager);
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
    connect(zv_trainingWidget, &ZTrainingWidget::zg_requestTaskFinish,
            zv_workController, &ZWorkController::zp_initTaskFinish);
    connect(zv_statisticsWidget, &ZStatisticsWidget::zg_requestStatisticsDisplayFinish,
            zv_workController, &ZWorkController::zp_initStatisticsDisplayFinish);

    connect(zv_workController, &ZWorkController::zg_setStackedWidgetIndex,
            zv_stackedWidget, &QStackedWidget::setCurrentIndex);

    connect(zv_workController, &ZWorkController::zg_requestTaskStart,
            zv_trainingManager, &ZTrainingManager::zp_initTaskStart);
    connect(zv_workController, &ZWorkController::zg_requestTaskFinish,
            zv_trainingManager, &ZTrainingManager::zp_stopTask);
    connect(zv_trainingWidget, &ZTrainingWidget::zg_requestTaskRestart,
            zv_trainingManager, &ZTrainingManager::zp_restartTask);
    connect(zv_trainingWidget, &ZTrainingWidget::zg_requestTaskPauseToggle,
            zv_trainingManager, &ZTrainingManager::zp_setTaskPaused);


    connect(zv_settingsAction, &QAction::triggered,
            this, &MainWindow::zh_runSettings);

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
void MainWindow::zh_runSettings()
{
    ZSettingsDialog dialog;
    dialog.zp_setTrainingManager(zv_trainingManager);
    dialog.zp_setTrainingWidget(zv_trainingWidget);

    zv_trainingManager->zp_setTaskPaused(true);
    dialog.exec();
    zv_trainingManager->zp_setTaskPaused(false);
}
//===================================================


