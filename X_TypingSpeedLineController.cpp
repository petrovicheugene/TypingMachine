//===================================================
#include "X_TypingSpeedLineController.h"
//===================================================
X_TypingSpeedLineController::X_TypingSpeedLineController(ZTask &task, QObject *parent)
    : X_AbstractLineController{task, parent}
{

}
//===================================================
QString X_TypingSpeedLineController::xp_nextLine(bool *completed)
{

    return "typing Speed";
}
//===================================================
void X_TypingSpeedLineController::xp_reset()
{

}
//===================================================

