//===================================================
#include "ZRandomLineController.h"
//===================================================
ZRandomLineController::ZRandomLineController(ZTask &task, QObject *parent) :
    ZAbstractLineController{task, parent}
{

}
//===================================================
QString ZRandomLineController::zp_nextLine()
{
    return "Random";
}
//===================================================
void ZRandomLineController::zp_reset()
{

}
//===================================================
