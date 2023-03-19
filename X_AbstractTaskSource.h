//===================================================
#ifndef X_ABSTRACTTASKSOURCE_H
#define X_ABSTRACTTASKSOURCE_H
//===================================================
#include <QObject>
#include "X_Task.h"
//===================================================
class QAbstractItemModel;
//===================================================
class X_AbstractTaskSource : public QObject
{
    Q_OBJECT
public:
    explicit X_AbstractTaskSource(QObject *parent = nullptr);

    virtual QAbstractItemModel* xp_taskModel() const = 0;
    virtual X_Task xp_taskForRow(int row) const= 0;


};
//===================================================
#endif // X_ABSTRACTTASKSOURCE_H
