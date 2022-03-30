//===================================================
#ifndef ZWORKCONTROLLER_H
#define ZWORKCONTROLLER_H
//===================================================
#include <QObject>
#include "ZTaskSource.h"
#include "ZTask.h"
//===================================================
class ZWorkController : public QObject
{
    Q_OBJECT
public:
    explicit ZWorkController(QObject *parent = nullptr);

    void zp_setTaskSource(ZTaskSource* taskSource);
    // void zp_connectToTaskSource(ZTaskSource* taskSource);


public slots:

    void zp_initTaskStart(int row);
    void zp_initTaskStop();

signals:

    void zg_setStackedWidgetIndex(int index);
    void zg_requestTaskStart(ZTask task);
    void zg_requestTaskStop();

private:

    // VARS
    ZTaskSource* zv_taskSource;
    // FUNCS

};
//===================================================
#endif // ZWORKCONTROLLER_H
