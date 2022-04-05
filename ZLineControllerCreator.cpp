//===================================================
#include "ZLineControllerCreator.h"
#include "ZRandomLineController.h"
#include "ZSuccessivelyLineController.h"
#include "ZTypingSpeedLineController.h"

//===================================================
ZAbstractLineController* ZLineControllerCreator::zp_createLineController(ZTask& task)
{
    OUTPUT_ORDER outputOrder = std::get<3>(task);

    switch(outputOrder)
    {
    case SUCCESSIVELY:
        return new ZSuccessivelyLineController(task);
    case RANDOM:
        return new ZRandomLineController(task);
    case TYPING_SPEED:
    default:
        return new ZTypingSpeedLineController(task);
    }




}
//===================================================
