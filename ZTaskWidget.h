//===================================================
#ifndef ZTASKWIDGET_H
#define ZTASKWIDGET_H
//===================================================
#include <QWidget>
//===================================================
class QSplitter;

class ZTaskManager;
class ZTaskListWidget;
class ZTaskContentWidget;
//===================================================
class ZTaskWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ZTaskWidget(QWidget *parent = nullptr);
    ~ZTaskWidget();

    void zp_connectToTaskManager(ZTaskManager* taskManager);

signals:


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
