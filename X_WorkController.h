//===================================================
#ifndef X_WORKCONTROLLER_H
#define X_WORKCONTROLLER_H
//===================================================
#include <QObject>
#include "X_AbstractTaskSource.h"
//#include "ZTask.h"
//===================================================
class X_WorkController : public QObject
{
    Q_OBJECT
public:
    explicit X_WorkController(QObject *parent = nullptr);

    void xp_setTaskSource(X_AbstractTaskSource *taskSource);
    // void xp_connectToTaskSource(ZTaskSource* taskSource);


public slots:

    void xp_initTaskStart(int row);
    void xp_initTaskFinish(bool statisticsReadiness);
    void xp_initStatisticsDisplayFinish();

signals:

    void xg_setStackedWidgetIndex(int index);
    void xg_requestTaskStart(X_Task task);
    void xg_requestTaskFinish();

private:

    // VARS
    X_AbstractTaskSource* xv_taskSource;
    // FUNCS

};
//===================================================
#endif // X_WORKCONTROLLER_H
