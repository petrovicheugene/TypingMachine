//===================================================
#ifndef ZSUCCESSIVELYLINECONTROLLER_H
#define ZSUCCESSIVELYLINECONTROLLER_H
//===================================================
#include "ZAbstractLineController.h"
//===================================================

//===================================================
class ZSuccessivelyLineController : public ZAbstractLineController
{
    Q_OBJECT
public:
    explicit ZSuccessivelyLineController(ZTask& task, QObject *parent = nullptr);

    QString zp_nextLine() override;
    void zp_reset() override;

private:

    // VARS
    bool zv_repeat;
    int zv_lineIndex;
    // FUNCS

};
//===================================================
#endif // ZSUCCESSIVELYLINECONTROLLER_H
