//===================================================
#include "MainWindow.h"

#include <QAction>
#include <QApplication>
#include <QDebug>
#include <QMenuBar>
#include <QPushButton>
#include <QSettings>
#include <QStyleFactory>

#include "ZAppSettings.h"
#include "ZDataSourceManager.h"
#include "ZSettingsDialog.h"
#include "ZTaskWidget.h"
#include "ZTrainingManager.h"
#include "ZTrainingWidget.h"
#include "ZWorkController.h"
//===================================================
Q_DECLARE_METATYPE(ZAppSettings);
//===================================================
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    qRegisterMetaType<ZAppSettings>();

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
    QMenu* mainMenu = new QMenu();
    mainMenu->setToolTip(tr("Main menu"));
    mainMenu->setIcon(QIcon(":images/menu-512.png"));
    menuBar()->addMenu(mainMenu);

    zv_settingsAction = new QAction(tr("Settings"));
    //zv_settingsAction->setToolTip(tr("Settings"));
    zv_settingsAction->setIcon(QIcon(":images/settings-01.png"));
    mainMenu->addAction(zv_settingsAction);

    zv_exitAction = new QAction(tr("Exit"));
    //zv_settingsAction->setToolTip(tr("Settings"));
    zv_exitAction->setIcon(QIcon(":images/exitDoor-256.png"));
    mainMenu->addAction(zv_exitAction);

//    zv_userButton = new QPushButton;
//    menuBar()->setCornerWidget(zv_userButton);

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
    connect(zv_trainingWidget, &ZTrainingWidget::zg_requestTaskFinish,
            zv_workController, &ZWorkController::zp_initTaskFinish);

    connect(zv_workController, &ZWorkController::zg_setStackedWidgetIndex,
            zv_stackedWidget, &QStackedWidget::setCurrentIndex);

    connect(zv_workController, &ZWorkController::zg_requestTaskStart,
            zv_trainingManager, &ZTrainingManager::zp_initTaskStart);
    connect(zv_workController, &ZWorkController::zg_requestTaskFinish,
            zv_trainingManager, &ZTrainingManager::zp_finishTask);
    connect(zv_trainingWidget, &ZTrainingWidget::zg_requestTaskRestart,
            zv_trainingManager, &ZTrainingManager::zp_restartTask);

    connect(zv_settingsAction, &QAction::triggered,
            this, &MainWindow::zh_runSettings);
    connect(zv_exitAction, &QAction::triggered,
            this, &MainWindow::close);

}
//===================================================
void MainWindow::zh_saveSettings()
{
    QSettings settings;
    settings.setValue("AppGeometry", saveGeometry());
    ZAppSettings appSettings;
    appSettings[SN_COMPLETED_COLOR] =  zv_trainingWidget->zp_completedColor();
    appSettings[SN_INCOMPLETED_COLOR] =  zv_trainingWidget->zp_incompletedColor();
    appSettings[SN_CURRENT_COLOR] =  zv_trainingWidget->zp_currentSymbolColor();
    appSettings[SN_WRONG_COLOR] =  zv_trainingWidget->zp_wrongSymbolColor();

    settings.setValue("AppSettings", QVariant::fromValue<ZAppSettings>(appSettings));
}
//===================================================
void MainWindow::zh_restoreSettings()
{
    QSettings settings;
    restoreGeometry(settings.value("AppGeometry").toByteArray());

    QVariant vData = settings.value("AppSettings");
    if(vData.canConvert<ZAppSettings>())
    {
        ZAppSettings appSettings = vData.value<ZAppSettings>();
        // zv_trainingWidget->zp_applySettings(appSettings);
        zv_trainingWidget->zp_setCompletedColor(appSettings.value(SN_COMPLETED_COLOR).value<QColor>());
        zv_trainingWidget->zp_setIncompletedColor(appSettings.value(SN_INCOMPLETED_COLOR).value<QColor>());
        zv_trainingWidget->zp_setCurrentSymbolColor(appSettings.value(SN_CURRENT_COLOR).value<QColor>());
        zv_trainingWidget->zp_setWrongSymbolColor(appSettings.value(SN_WRONG_COLOR).value<QColor>());
    }
}
//===================================================
void MainWindow::zh_runSettings()
{
    ZSettingsDialog dialog;
    dialog.exec();

    qDebug() << "SETTINGS";
}
//===================================================


