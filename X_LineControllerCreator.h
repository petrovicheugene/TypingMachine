//===================================================
#ifndef X_LINECONTROLLERCREATOR_H
#define X_LINECONTROLLERCREATOR_H
//===================================================
#include "X_Task.h"
//===================================================
class X_AbstractLineController;
//===================================================
class X_LineControllerCreator
{
public:
    static X_AbstractLineController* xp_createLineController(X_Task& task);


};
//===================================================
#endif // X_LINECONTROLLERCREATOR_H
