//===================================================
#ifndef X_TASKLISTWIDGET_H
#define X_TASKLISTWIDGET_H
//===================================================
#include <QWidget>
//===================================================
class QAbstractItemModel;
class QPushButton;
class QTableView;

//===================================================
class X_TaskListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit X_TaskListWidget(QWidget *parent = nullptr);

    void xp_setTaskModel(QAbstractItemModel* model);
    int xp_currentTaskRow() const;

signals:

    void xg_requestNewTaskCreation();
    void xg_requestTasksRemoving(QVector<int> rows);
    void xg_currentTaskChanged(int row);

private slots:

    // task model
    void xh_initNewTaskCreation();
    void xh_initTaskRemoving();
    // void xh_initTaskRunning();
    void xh_onNewTaskInserting(const QModelIndex &index, int first, int last);
    void xh_onCurrentRowChange(const QModelIndex &current,
                               const QModelIndex & previous);
private:
    // VARS
    QPushButton* xv_newTaskButton;
    QPushButton* xv_deleteTasklButton;
    //QPushButton* xv_runTaskButton;

    QTableView* xv_taskListView;

    // FUNCS
    void xh_createComponents();
    void xh_createConnections();

};
//===================================================
#endif // X_TASKLISTWIDGET_H
