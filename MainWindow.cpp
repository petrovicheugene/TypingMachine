//===================================================
#include "MainWindow.h"

#include <QAction>
#include <QApplication>
#include <QDebug>
#include <QMenuBar>
#include <QPushButton>
#include <QSettings>
#include <QStyleFactory>

#include "X_DataSourceManager.h"
#include "X_SettingsDialog.h"
#include "X_StatisticsWidget.h"
#include "X_SessionStatisticsManager.h"
#include "X_TaskWidget.h"
#include "X_TrainingManager.h"
#include "X_TrainingWidget.h"
#include "X_WorkController.h"

//===================================================
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    setWindowTitle(qApp->applicationDisplayName());

    xh_createComponents();
    xh_createConnections();

    qApp->setStyle(QStyleFactory::create("Fusion"));
    QPalette p = QPalette(Qt::darkGray);
    p.setColor(QPalette::Window, QColor(30,30,30));
    p.setColor(QPalette::Button, QColor(53,53,53));
    p.setColor(QPalette::Highlight, QColor(60,60,60));
    p.setColor(QPalette::ButtonText, QColor(255,255,255));
    p.setColor(QPalette::WindowText, QColor(255,255,255));
    qApp->setPalette(p);

    xh_restoreSettings();
}
//===================================================
MainWindow::~MainWindow()
{
    // disconnect from database
    xh_saveSettings();
}
//===================================================
void MainWindow::xh_createComponents()
{
    // Menu
//    QMenu* mainMenu = new QMenu();
//    mainMenu->setToolTip(tr("Main menu"));
//    mainMenu->setIcon(QIcon(":images/menu-512.png"));
//    menuBar()->addMenu(mainMenu);

    xv_settingsAction = new QAction;
    //xv_settingsAction->setToolTip(tr("Settings"));
    xv_settingsAction->setIcon(QIcon(":images/settings-01.png"));
    menuBar()->addAction(xv_settingsAction);

//    xv_userButton = new QPushButton;
//    menuBar()->setCornerWidget(xv_userButton);

    // Central widget
    xv_stackedWidget = new QStackedWidget;
    setCentralWidget(xv_stackedWidget);

    // create widgets and add  to stacked widget
    xv_taskWidget = new X_TaskWidget;
    xv_trainingWidget = new X_TrainingWidget;
    xv_statisticsWidget = new X_StatisticsWidget;

    xv_stackedWidget->addWidget(xv_taskWidget);
    xv_stackedWidget->addWidget(xv_trainingWidget);
    xv_stackedWidget->addWidget(xv_statisticsWidget);

    // task model
    xv_dataSourceManager = new X_DataSourceManager(this);
    xv_taskWidget->xp_setTaskModel(xv_dataSourceManager->xp_taskModel());

    // statistics model
    xv_statisticsWidget->xp_setStatisticsModel(xv_dataSourceManager->xp_statisticsModel());

    // training manager
    xv_trainingManager = new X_TrainingManager(this);
    xv_trainingWidget->xp_connectToTrainingManager(xv_trainingManager);

    xv_workController = new X_WorkController(this);
    xv_workController->xp_setTaskSource(xv_dataSourceManager);

    // task Statistics manager
    xv_taskStatisticsManager = new X_SessionStatisticsManager(this);
    xv_taskStatisticsManager->xp_setTrainingManager(xv_trainingManager);
    xv_taskStatisticsManager->xp_setStatisticsSource(xv_dataSourceManager);
}
//===================================================
void MainWindow::xh_createConnections()
{
    connect(xv_taskWidget, &X_TaskWidget::xg_requestNewTaskCreation,
            xv_dataSourceManager, &X_DataSourceManager::xp_createNewTask);
    connect(xv_taskWidget, &X_TaskWidget::xg_requestTasksRemoving,
            xv_dataSourceManager, &X_DataSourceManager::xp_deleteTasks);

    // work controller connections
    connect(xv_taskWidget, &X_TaskWidget::xg_requestTaskRun,
            xv_workController, &X_WorkController::xp_initTaskStart);
    connect(xv_taskStatisticsManager, &X_SessionStatisticsManager::xg_taskStatisticsReadiness,
            xv_workController, &X_WorkController::xp_initTaskFinish);

    connect(xv_statisticsWidget, &X_StatisticsWidget::xg_requestStatisticsDisplayFinish,
            xv_workController, &X_WorkController::xp_initStatisticsDisplayFinish);

    connect(xv_workController, &X_WorkController::xg_setStackedWidgetIndex,
            xv_stackedWidget, &QStackedWidget::setCurrentIndex);

    connect(xv_workController, &X_WorkController::xg_requestTaskStart,
            xv_trainingManager, &X_TrainingManager::xp_initTaskStart);
    connect(xv_workController, &X_WorkController::xg_requestTaskFinish,
            xv_trainingManager, &X_TrainingManager::xp_stopTask);
    connect(xv_trainingWidget, &X_TrainingWidget::xg_requestTaskRestart,
            xv_trainingManager, &X_TrainingManager::xp_restartTask);
    connect(xv_trainingWidget, &X_TrainingWidget::xg_requestTaskPauseSwitch,
            xv_trainingManager, &X_TrainingManager::xp_switchTaskPaused);

    connect(xv_settingsAction, &QAction::triggered,
            this, &MainWindow::xh_runSettings);

}
//===================================================
void MainWindow::xh_saveSettings()
{
    QSettings settings;
    settings.setValue("AppGeometry", saveGeometry());
}
//===================================================
void MainWindow::xh_restoreSettings()
{
    QSettings settings;
    restoreGeometry(settings.value("AppGeometry").toByteArray());
}
//===================================================
void MainWindow::xh_runSettings()
{
    X_SettingsDialog dialog;
    dialog.xp_setTrainingManager(xv_trainingManager);
    dialog.xp_setTrainingWidget(xv_trainingWidget);

    xv_trainingManager->xp_switchTaskPaused(true);
    dialog.exec();
    xv_trainingManager->xp_switchTaskPaused(false);
}
//===================================================


