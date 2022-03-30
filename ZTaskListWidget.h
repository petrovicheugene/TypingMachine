//===================================================
#ifndef ZTASKLISTWIDGET_H
#define ZTASKLISTWIDGET_H
//===================================================
#include <QWidget>
//===================================================
class QAbstractItemModel;
class QPushButton;
class QTableView;

//===================================================
class ZTaskListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ZTaskListWidget(QWidget *parent = nullptr);

    void zp_setTaskModel(QAbstractItemModel* model);
    int zp_currentTaskRow() const;

signals:

    void zg_requestNewTaskCreation();
    void zg_requestTasksRemoving(QVector<int> rows);
    void zg_currentTaskChanged(int row);

private slots:

    // task model
    void zh_initNewTaskCreation();
    void zh_initTaskRemoving();
    // void zh_initTaskRunning();
    void zh_onNewTaskInserting(const QModelIndex &index, int first, int last);
    void zh_onCurrentRowChange(const QModelIndex &current,
                               const QModelIndex & previous);
private:
    // VARS
    QPushButton* zv_newTaskButton;
    QPushButton* zv_deleteTasklButton;
    //QPushButton* zv_runTaskButton;

    QTableView* zv_taskListView;

    // FUNCS
    void zh_createComponents();
    void zh_createConnections();

};
//===================================================
#endif // ZTASKLISTWIDGET_H
