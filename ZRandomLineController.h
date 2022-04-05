//===================================================
#ifndef ZRANDOMLINECONTROLLER_H
#define ZRANDOMLINECONTROLLER_H
//===================================================
#include "ZAbstractLineController.h"
//===================================================
class ZRandomLineController : public ZAbstractLineController
{
    Q_OBJECT
public:
    explicit ZRandomLineController(ZTask& task, QObject* parent = nullptr);

    QString zp_nextLine() override;
    void zp_reset() override;

};
//===================================================
#endif // ZRANDOMLINECONTROLLER_H
