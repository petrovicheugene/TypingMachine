//===================================================
#ifndef X_TYPINGSPEEDLINECONTROLLER_H
#define X_TYPINGSPEEDLINECONTROLLER_H
//===================================================
#include "X_AbstractLineController.h"
//===================================================

//===================================================
class X_TypingSpeedLineController : public X_AbstractLineController
{
    Q_OBJECT
public:
    explicit X_TypingSpeedLineController(ZTask& task, QObject *parent = nullptr);

    QString xp_nextLine(bool* completed = nullptr)  override;
    void xp_reset() override;

signals:

};
//===================================================
#endif // X_TYPINGSPEEDLINECONTROLLER_H
