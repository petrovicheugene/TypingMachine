//===================================================
#ifndef ZTYPINGSPEEDLINECONTROLLER_H
#define ZTYPINGSPEEDLINECONTROLLER_H
//===================================================
#include "ZAbstractLineController.h"
//===================================================

//===================================================
class ZTypingSpeedLineController : public ZAbstractLineController
{
    Q_OBJECT
public:
    explicit ZTypingSpeedLineController(ZTask& task, QObject *parent = nullptr);

    QString zp_nextLine()  override;
    void zp_reset() override;

signals:

};
//===================================================
#endif // ZTYPINGSPEEDLINECONTROLLER_H
