//===================================================
#ifndef ZTASKMODEL_H
#define ZTASKMODEL_H
//===================================================
#include <QSqlTableModel>
//===================================================
class ZTaskModel : public QSqlTableModel
{
    Q_OBJECT
public:
    explicit ZTaskModel(QObject *parent = nullptr);
    ~ZTaskModel();

public slots:

    void zp_createNewTask();

signals:



private:
    // VARS
    const QString zv_databaseFileName = "database.sqlite";

    // FUNCS
    bool zh_checkDatabase() const;
    void zh_createNewDatabase();
    bool zh_connectToDatabase();

};
//===================================================
#endif // ZTASKMODEL_H
