//===================================================
#ifndef X_ABSTRACTLINECONTROLLER_H
#define X_ABSTRACTLINECONTROLLER_H
//===================================================
#include <QObject>
#include "X_Task.h"
//===================================================

//===================================================
class X_AbstractLineController : public QObject
{
    Q_OBJECT
public:
    explicit X_AbstractLineController(X_Task& task, QObject *parent = nullptr);

    virtual QString xp_nextLine(bool* completed = nullptr)  = 0;
    virtual void xp_reset() = 0;

signals:


protected:

    // VARS
    QStringList xv_lineList;


};
//===================================================
#endif // X_ABSTRACTLINECONTROLLER_H
