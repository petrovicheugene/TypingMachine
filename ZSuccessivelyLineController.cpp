//===================================================
#include "ZSuccessivelyLineController.h"
//===================================================
ZSuccessivelyLineController::ZSuccessivelyLineController(ZTask &task, QObject *parent)
    : ZAbstractLineController{task, parent}
{
    zv_lineIndex = 0;
    zv_repeat = std::get<5>(task);
}
//===================================================
QString ZSuccessivelyLineController::zp_nextLine()
{
    if(zv_lineList.isEmpty())
    {
        emit zg_taskCompleted();
        return QString();
    }

    if(zv_lineIndex == zv_lineList.count())
    {
        zv_lineIndex = 0;
        if(!zv_repeat)
        {
            emit zg_taskCompleted();
            return QString();
        }
    }

    return zv_lineList.at(zv_lineIndex++);
}
//===================================================
void ZSuccessivelyLineController::zp_reset()
{
    zv_lineIndex = 0;
}
//===================================================

