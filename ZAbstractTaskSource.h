//===================================================
#ifndef ZABSTRACTTASKSOURCE_H
#define ZABSTRACTTASKSOURCE_H
//===================================================
#include <QObject>
#include "ZTask.h"
//===================================================
class QAbstractItemModel;
//===================================================
class ZAbstractTaskSource : public QObject
{
    Q_OBJECT
public:
    explicit ZAbstractTaskSource(QObject *parent = nullptr);

    virtual QAbstractItemModel* zp_taskModel() const = 0;
    virtual ZTask zp_taskForRow(int row) const= 0;


};
//===================================================
#endif // ZABSTRACTTASKSOURCE_H
