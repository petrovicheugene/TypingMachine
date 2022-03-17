//===================================================
#ifndef ZTASKMANAGER_H
#define ZTASKMANAGER_H
//===================================================
#include <QObject>
//===================================================
class QAbstractItemModel;
//===================================================
class ZTaskManager : public QObject
{
    Q_OBJECT
public:
    explicit ZTaskManager(QObject *parent = nullptr);

    QAbstractItemModel* zp_taskModel() const;

signals:


private:

    // VARS
    QAbstractItemModel* zv_model;

    // FUNCS

    void zh_createComponents();
    void zh_createConnections();

};
//===================================================
#endif // ZTASKMANAGER_H
