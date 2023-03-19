//===================================================
#include "X_SuccessivelyLineController.h"
//===================================================
X_SuccessivelyLineController::X_SuccessivelyLineController(X_Task &task, QObject *parent)
    : X_AbstractLineController{task, parent}
{
    xv_lineIndex = 0;
    xv_repeat = std::get<5>(task);
}
//===================================================
QString X_SuccessivelyLineController::xp_nextLine(bool *completed)
{
    if(xv_lineList.isEmpty())
    {
        if(completed)
        {
            *completed = true;
        }        return QString();
    }

    if(xv_lineIndex == xv_lineList.count())
    {
        xv_lineIndex = 0;
        if(!xv_repeat)
        {
            if(completed)
            {
                *completed = true;
            }
            return QString();
        }
    }

    if(completed)
    {
        *completed = false;
    }
    return xv_lineList.at(xv_lineIndex++);
}
//===================================================
void X_SuccessivelyLineController::xp_reset()
{
    xv_lineIndex = 0;
}
//===================================================

