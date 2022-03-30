//===================================================
#include "ZTaskModel.h"

#include <QDebug>
#include <QDir>

#include <QFile>

#include <QMessageBox>
#include <QSqlError>
//===================================================
ZTaskModel::ZTaskModel(QObject *parent)
    : QSqlTableModel{parent}
{
    zh_connectToDatabase();
//    if(zh_checkDatabase())
//    {
//        zh_createNewDatabase();
//    }

    // QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");

}
//===================================================
ZTaskModel::~ZTaskModel()
{
    if(database().isOpen())
    {
        database().close();
    }
}
//===================================================
bool ZTaskModel::zh_connectToDatabase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(zv_databaseFileName);
    if(!db.open())
    {
        QString msg = tr("Cannot open database \"%1\". \nError: %2").arg(zv_databaseFileName, db.lastError().text()) ;
        QMessageBox::critical(nullptr, "Error", msg, QMessageBox::Ok);
        return false;
    }


    return false;
}
//===================================================
bool ZTaskModel::zh_checkDatabase() const
{
    return false;
}
//===================================================
void ZTaskModel::zh_createNewDatabase()
{
    qDebug() << database().tables();
}
//===================================================
void ZTaskModel::zp_createNewTask()
{
    bool res = insertRows(rowCount(), 1);
    setData(index(rowCount() - 1, 0),  rowCount() - 1);
    setData(index(rowCount() - 1, 1),  "RTY");
    setData(index(rowCount() - 1, 2),  "DFG");
    submitAll();
    qDebug() << "INSERT ROWS" << res << rowCount();
}
//===================================================



