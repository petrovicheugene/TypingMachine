//===================================================
#ifndef DIALOG_H
#define DIALOG_H
//===================================================
#include <QMainWindow>
#include <QStackedWidget>
//===================================================
class ZDataSourceManager;
class ZTaskWidget;

class ZTrainingManager;
class ZTrainingWidget;
class ZWorkController;
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
    ZWorkController* zv_workController;
    QStackedWidget* zv_stackedWidget;
    ZTrainingWidget* zv_trainingWidget;
    ZTaskWidget* zv_taskWidget;

    ZTrainingManager* zv_trainingManager;
    ZDataSourceManager* zv_dataSourceManager;

    // FUNCS
    void zh_createComponents();
    void zh_createConnections();

    void zh_saveSettings();
    void zh_restoreSettings();



};
//===================================================
#endif // DIALOG_H