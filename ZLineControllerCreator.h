//===================================================
#ifndef ZLINECONTROLLERCREATOR_H
#define ZLINECONTROLLERCREATOR_H
//===================================================
#include "ZTask.h"
//===================================================
class ZAbstractLineController;
//===================================================
class ZLineControllerCreator
{
public:
    static ZAbstractLineController* zp_createLineController(ZTask& task);


};
//===================================================
#endif // ZLINECONTROLLERCREATOR_H
