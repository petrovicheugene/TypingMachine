//===================================================
#ifndef X_SUCCESSIVELYLINECONTROLLER_H
#define X_SUCCESSIVELYLINECONTROLLER_H
//===================================================
#include "X_AbstractLineController.h"
//===================================================

//===================================================
class X_SuccessivelyLineController : public X_AbstractLineController
{
    Q_OBJECT
public:
    explicit X_SuccessivelyLineController(X_Task& task, QObject *parent = nullptr);

    QString xp_nextLine(bool* completed = nullptr) override;
    void xp_reset() override;

private:

    // VARS
    bool xv_repeat;
    int xv_lineIndex;
    // FUNCS

};
//===================================================
#endif // X_SUCCESSIVELYLINECONTROLLER_H
