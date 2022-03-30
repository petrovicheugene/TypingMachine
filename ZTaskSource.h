//===================================================
#ifndef ZTASKSOURCE_H
#define ZTASKSOURCE_H
//===================================================
#include <QObject>
#include "ZTask.h"
//===================================================
class ZTaskSource : public QObject
{
    Q_OBJECT
public:
    explicit ZTaskSource(QObject *parent = nullptr);

    virtual ZTask zp_taskForRow(int row) const= 0;

signals:

};
//===================================================
#endif // ZTASKSOURCE_H
