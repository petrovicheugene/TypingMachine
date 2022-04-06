//===================================================
#ifndef ZDATASOURCEMANAGER_H
#define ZDATASOURCEMANAGER_H
//===================================================
#include "ZTaskSource.h"
//===================================================
class QAbstractItemModel;
class QSqlTableModel;
//===================================================
class ZDataSourceManager : public ZTaskSource
{
    Q_OBJECT
public:
    explicit ZDataSourceManager(QObject *parent = nullptr);
    ~ZDataSourceManager();

    QAbstractItemModel* zp_taskModel() const;

    ZTask zp_taskForRow(int row) const override;

public slots:

    void zp_createNewTask();
    void zp_deleteTasks(QVector<int> rows);

signals:

private:

    // VARS
    const QString zv_default_user_name = "default_user";
    QSqlTableModel* zv_taskModel;
    const QString zv_databaseName = "typing_training.sqlite";

    // FUNCS
    bool zh_connectToDatabase();
    void zh_createComponents();
    void zh_createConnections();
    bool zh_reviseDatabaseTables();
    void zh_reviseDefaultUser();

    int zh_findNextTaskNum() const;


};
 //===================================================
#endif // ZDATASOURCEMANAGER_H
