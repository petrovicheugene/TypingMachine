//===================================================
#include "X_RandomLineController.h"
#include <QDebug>
//===================================================
X_RandomLineController::X_RandomLineController(X_Task &task, QObject *parent) :
    X_AbstractLineController{task, parent}
{
    xv_index = 0;
    xv_repeat = std::get<5>(task);
    xh_initIndices();
    xh_suffleIndices();
}
//===================================================
QString X_RandomLineController::xp_nextLine(bool *completed)
{
    if(xv_lineList.isEmpty())
    {
       if(completed)
       {
           *completed = true;
       }
        // emit xg_taskCompleted();
        return QString();
    }

    if(xv_index == xv_lineList.count())
    {
        xv_index = 0;
        xh_suffleIndices();
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

    return xv_lineList.at(xv_lineIndices.at(xv_index++));
}
//===================================================
void X_RandomLineController::xp_reset()
{
    xv_index = 0;
    xh_initIndices();

}
//===================================================
void X_RandomLineController::xh_initIndices()
{
    for(int i = 0; i < xv_lineList.count(); ++i)
    {
        xv_lineIndices.append(i);
    }
}
//===================================================
void X_RandomLineController::xh_suffleIndices()
{
    std::random_shuffle(xv_lineIndices.begin(), xv_lineIndices.end());
}
//===================================================


