//===================================================
#include "X_LineControllerCreator.h"
#include "X_RandomLineController.h"
#include "X_SuccessivelyLineController.h"
#include "X_TypingSpeedLineController.h"

//===================================================
X_AbstractLineController* X_LineControllerCreator::xp_createLineController(X_Task& task)
{
    OUTPUT_ORDER outputOrder = std::get<3>(task);

    switch(outputOrder)
    {
    case SUCCESSIVELY:
        return new X_SuccessivelyLineController(task);
    case RANDOM:
        return new X_RandomLineController(task);
    case TYPING_SPEED:
    default:
        return new X_TypingSpeedLineController(task);
    }
}
//===================================================
