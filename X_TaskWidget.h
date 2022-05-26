//===================================================
#ifndef X_TASKWIDGET_H
#define X_TASKWIDGET_H
//===================================================
#include <QWidget>
//===================================================
class QAbstractItemModel;
class QSplitter;

class X_TrainingManager;
class X_TaskListWidget;
class X_TaskContentWidget;
//===================================================
class X_TaskWidget : public QWidget
{
    Q_OBJECT
public:
    explicit X_TaskWidget(QWidget *parent = nullptr);
    ~X_TaskWidget();

    void xp_setTaskModel(QAbstractItemModel* model);
    void  xp_applySettings(QMap<int, QVariant>);
    QMap<int, QVariant> xp_settings();

signals:

    void xg_requestNewTaskCreation();
    void xg_requestTasksRemoving(QVector<int> rows);
    void xg_requestTaskRun(int row);

private slots:

    void xh_initTaskRun();

private:

    // VARS
    X_TaskListWidget* xv_taskListWidget;
    X_TaskContentWidget* xv_taskContentWidget;
    QSplitter* xv_splitter;


    // FUNCS
    void xh_createComponents();
    void xh_createConnections();

    void xh_saveSettings();
    void xh_restoreSettings();

};
//===================================================
#endif // X_TASKWIDGET_H
