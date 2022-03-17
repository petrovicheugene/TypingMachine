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

    void zp_setModelToView(QAbstractItemModel* model);


signals:

private:
    // VARS
    QPushButton* zv_newTaskButton;
    QPushButton* zv_deleteTasklButton;
    QPushButton* zv_runTaskButton;

    QTableView* zv_taskListView;

    // FUNCS
    void zh_createComponents();
    void zh_createConnections();

};
//===================================================
#endif // ZTASKLISTWIDGET_H
