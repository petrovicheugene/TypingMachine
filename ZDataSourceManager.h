//===================================================
#ifndef ZDATASOURCEMANAGER_H
#define ZDATASOURCEMANAGER_H
//===================================================
#include "ZAbstractTaskSource.h"
#include "ZAbstractStatisticsSource.h"
//===================================================
class QAbstractItemModel;
class QSqlTableModel;

class QStandardItemModel;
//===================================================
class ZDataSourceManager : public ZAbstractTaskSource, public ZAbstractStatisticsSource
{
    Q_OBJECT
public:
    explicit ZDataSourceManager(QObject *parent = nullptr);
    ~ZDataSourceManager();

    QAbstractItemModel* zp_taskModel() const override;
    ZTask zp_taskForRow(int row) const override;

    QAbstractItemModel* zp_statisticsModel() const override;
    void zp_loadTaskStatistics(QMap<QString, WordStatistics>& taskStatistics) override;

public slots:

    void zp_createNewTask();
    void zp_deleteTasks(QVector<int> rows);

signals:

private:

    // VARS
    const QString zv_default_user_name = "default_user";
    const QString zv_databaseName = "typing_training.sqlite";
    QSqlTableModel* zv_taskModel;

    QStandardItemModel* zv_statisticsModel;

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
