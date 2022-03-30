//===================================================
#ifndef ZTASKWIDGET_H
#define ZTASKWIDGET_H
//===================================================
#include <QWidget>
//===================================================
class QAbstractItemModel;
class QSplitter;

class ZTrainingManager;
class ZTaskListWidget;
class ZTaskContentWidget;
//===================================================
class ZTaskWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ZTaskWidget(QWidget *parent = nullptr);
    ~ZTaskWidget();

    void zp_setTaskModel(QAbstractItemModel* model);

signals:

    void zg_requestNewTaskCreation();
    void zg_requestTasksRemoving(QVector<int> rows);
    void zg_requestTaskRun(int row);

private slots:

    void zh_initTaskRun();

private:

    // VARS
    ZTaskListWidget* zv_taskListWidget;
    ZTaskContentWidget* zv_taskContentWidget;
    QSplitter* zv_splitter;


    // FUNCS
    void zh_createComponents();
    void zh_createConnections();

    void zh_saveSettings();
    void zh_restoreSettings();

};
//===================================================
#endif // ZTASKWIDGET_H
