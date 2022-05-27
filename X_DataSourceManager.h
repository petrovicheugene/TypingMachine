//===================================================
#ifndef X_DATASOURCEMANAGER_H
#define X_DATASOURCEMANAGER_H
//===================================================
#include "X_AbstractTaskSource.h"
#include "X_AbstractStatisticsSource.h"
//===================================================
class QAbstractItemModel;
class QSqlTableModel;

class QStandardItemModel;
//===================================================
class X_DataSourceManager : public X_AbstractTaskSource, public X_AbstractStatisticsSource
{
    Q_OBJECT
public:
    explicit X_DataSourceManager(QObject *parent = nullptr);
    ~X_DataSourceManager();

    QAbstractItemModel* xp_taskModel() const override;
    ZTask xp_taskForRow(int row) const override;

    QAbstractItemModel* xp_statisticsModel() const override;
    void xp_loadTaskStatistics(QMap<QString, WordStatistics>& taskStatistics) override;

public slots:

    void xp_createNewTask();
    void xp_deleteTasks(QVector<int> rows);

signals:

private:

    // VARS
    const QString xv_default_user_name = "default_user";
    const QString xv_databaseName = "typing_machine.sqlite";
    QSqlTableModel* xv_taskModel;

    QStandardItemModel* xv_statisticsModel;

    // FUNCS
    bool xh_connectToDatabase();
    void xh_createComponents();
    void xh_createConnections();
    bool xh_reviseDatabaseTables();
    void xh_reviseDefaultUser();

    int xh_findNextTaskNum() const;

};
 //===================================================
#endif // X_DATASOURCEMANAGER_H
