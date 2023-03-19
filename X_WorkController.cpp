//===================================================
#include "X_WorkController.h"
//===================================================

//===================================================
X_WorkController::X_WorkController(QObject *parent)
    : QObject{parent}
{
    xv_taskSource = nullptr;
}
//===================================================
void X_WorkController::xp_setTaskSource(X_AbstractTaskSource* taskSource)
{
    xv_taskSource = taskSource;
}
//===================================================
void X_WorkController::xp_initTaskStart(int row)
{
    if(!xv_taskSource)
    {
        return;
    }
    
    X_Task task = xv_taskSource->xp_taskForRow(row);
    emit xg_setStackedWidgetIndex(1);
    emit xg_requestTaskStart(task);
}
//===================================================
void X_WorkController::xp_initTaskFinish(bool statisticsReadiness)
{
    //emit xg_requestTaskFinish();
    if(statisticsReadiness)
    {
        emit xg_setStackedWidgetIndex(2);
    }
    else
    {
        emit xg_setStackedWidgetIndex(0);
    }
 }
//===================================================
void X_WorkController::xp_initStatisticsDisplayFinish()
{
    emit xg_setStackedWidgetIndex(0);
}
//===================================================

