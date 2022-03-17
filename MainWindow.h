//===================================================
#ifndef DIALOG_H
#define DIALOG_H
//===================================================
#include <QMainWindow>
#include <QStackedWidget>
//===================================================
class ZTaskManager;
class ZTaskWidget;
class ZTrainingWidget;

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
    QStackedWidget* zv_stackedWidget;
    ZTrainingWidget* zv_trainingWidget;
    ZTaskWidget* zv_taskWidget;

    ZTaskManager* zv_taskManager;
    // FUNCS
    void zh_createComponents();
    void zh_createConnections();

    void zh_saveSettings();
    void zh_restoreSettings();



};
//===================================================
#endif // DIALOG_H
