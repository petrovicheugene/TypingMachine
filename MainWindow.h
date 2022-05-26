//===================================================
#ifndef DIALOG_H
#define DIALOG_H
//===================================================
#include <QMainWindow>
#include <QStackedWidget>
//===================================================
class QAction;
class QPushButton;

class X_DataSourceManager;
class X_StatisticsWidget;
class X_SessionStatisticsManager;
class X_TaskWidget;
class X_TrainingManager;
class X_TrainingWidget;
class X_WorkController;

//===================================================
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

private:
    // VARS

    QAction* xv_settingsAction;

    QStackedWidget* xv_stackedWidget;

    X_WorkController* xv_workController;
    X_TrainingWidget* xv_trainingWidget;
    X_TaskWidget* xv_taskWidget;
    X_StatisticsWidget* xv_statisticsWidget;

    X_TrainingManager* xv_trainingManager;
    X_SessionStatisticsManager* xv_taskStatisticsManager;
    X_DataSourceManager* xv_dataSourceManager;

    // FUNCS
    void xh_createComponents();
    void xh_createConnections();

    void xh_saveSettings();
    void xh_restoreSettings();

    void xh_runSettings();

};
//===================================================
#endif // DIALOG_H
