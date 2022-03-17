//===================================================
#include "MainWindow.h"

#include <QAction>
#include <QApplication>
#include <QDebug>
#include <QMenuBar>
#include <QSettings>
#include <QStyleFactory>

#include "ZTaskManager.h"
#include "ZTaskWidget.h"
#include "ZTrainingWidget.h"
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
    QAction* action = new QAction("Action");
    menuBar()->addAction(action);

    zv_stackedWidget = new QStackedWidget();
    setCentralWidget(zv_stackedWidget);

    zv_taskWidget = new ZTaskWidget;
    zv_trainingWidget = new ZTrainingWidget;

    zv_stackedWidget->addWidget(zv_taskWidget);
    zv_stackedWidget->addWidget(zv_trainingWidget);

    zv_taskManager = new ZTaskManager;

    zv_taskWidget->zp_connectToTaskManager(zv_taskManager);
    zv_trainingWidget->zp_connectToTaskManager(zv_taskManager);
}
//===================================================
void MainWindow::zh_createConnections()
{

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

