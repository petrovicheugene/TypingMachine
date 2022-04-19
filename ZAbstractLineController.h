//===================================================
#ifndef ZABSTRACTLINECONTROLLER_H
#define ZABSTRACTLINECONTROLLER_H
//===================================================
#include <QObject>
#include "ZTask.h"
//===================================================

//===================================================
class ZAbstractLineController : public QObject
{
    Q_OBJECT
public:
    explicit ZAbstractLineController(ZTask& task, QObject *parent = nullptr);

    virtual QString zp_nextLine(bool* completed = nullptr)  = 0;
    virtual void zp_reset() = 0;

signals:


protected:

    // VARS
    QStringList zv_lineList;


};
//===================================================
#endif // ZABSTRACTLINECONTROLLER_H
