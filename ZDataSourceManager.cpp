//===================================================
#include "ZDataSourceManager.h"
#include "ZSqlTableStatements.h"

#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QMessageBox>
#include <QRegularExpression>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlTableModel>

//===================================================
//===================================================
ZDataSourceManager::ZDataSourceManager(QObject *parent)
    : ZTaskSource{parent}
{
    if(!zh_connectToDatabase())
    {
        throw;
    }

    if(!zh_reviseDatabaseTables())
    {
        throw;
    }

    zh_reviseDefaultUser();

    zh_createComponents();
    zh_createConnections();
}
//===================================================
ZDataSourceManager::~ZDataSourceManager()
{
    zv_taskModel->submitAll();

    {
        QSqlDatabase db = QSqlDatabase::database();
       db.close();
    }
    QSqlDatabase::removeDatabase( QSqlDatabase::defaultConnection );
}
//===================================================
QAbstractItemModel* ZDataSourceManager::zp_taskModel() const
{
    return zv_taskModel;
}
//===================================================
bool ZDataSourceManager::zh_connectToDatabase()
{
    QStringList paths = QCoreApplication::libraryPaths();
    paths.append(".");
    paths.append("sqldrivers");
    QCoreApplication::setLibraryPaths(paths);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(zv_databaseName);

    if(!db.open())
    {
        QString msg = tr("Error connecting to database \"%1\". \nError: %2")
                .arg(zv_databaseName, db.lastError().text());
        QMessageBox::critical(nullptr, tr("Database error"), msg, QMessageBox::Ok);
        return false;
    }

    return true;
}
//===================================================
void ZDataSourceManager::zh_createComponents()
{
    zv_taskModel = new QSqlTableModel(this);
    zv_taskModel->setTable("tasks");
    zv_taskModel->setHeaderData(1, Qt::Horizontal,QVariant(tr("Task")));
    zv_taskModel->select();

}
//===================================================
void ZDataSourceManager::zh_createConnections()
{

}
//===================================================
bool ZDataSourceManager::zh_reviseDatabaseTables()
{
    QSqlDatabase db = QSqlDatabase::database();
    QStringList tableList = db.tables();

    QStringList sqlFiles = QDir::current().entryList(QStringList({"*.sql"}), QDir::Files);
    if(sqlFiles.isEmpty())
    {
        QString msg = tr("It is no sql script file in directory \"%1\" for the database revision.").arg(QDir::currentPath());
        QMessageBox::warning(nullptr, tr(""), msg, QMessageBox::Ok);
        return false;
    }

    QString sqlFilePath = "./" + sqlFiles.at(0);

    QFile file(sqlFilePath);
    if(!file.open(QIODevice::ReadOnly))
    {
        QString msg = tr("Cannot open file with error: \"%1\".").arg(file.errorString());
        QMessageBox::warning(nullptr, tr("Error"), msg, QMessageBox::Ok);

        return false;
    }

    // parse sql statements
    QTextStream textStream(&file);
    QString line;
    QString sqlStatement;
    // query
    QSqlQuery query(db);
    query.setForwardOnly(true);
    while(!textStream.atEnd())
    {
        line = textStream.readLine();
        // comments
        if(line.isEmpty() || line.startsWith("--") || line.startsWith("//") || line.startsWith("/*"))
        {
            continue;
        }

        sqlStatement += line;

        // end of statement
        if(!sqlStatement.endsWith(";"))
        {
            continue;
        }

        if(sqlStatement.startsWith("CREATE TABLE", Qt::CaseInsensitive))
        {
            static QRegularExpression re("[\\s,(]");
            QString tableName = sqlStatement.split(re).at(2);
            tableName = tableName.remove('"');
            if(!tableList.contains(tableName))
            {
                if(!query.exec(sqlStatement))
                {
                    QString msg = tr("The SQL statement \"%1\" has been executed with error: \"%2\"!").arg(sqlStatement, query.lastError().text());
                    QMessageBox::warning(nullptr, tr("SQL Error"), msg, QMessageBox::Ok);
                    file.close();
                    return false;
                }
            }
        }

        sqlStatement.clear();
    }

    file.close();
    return true;

}
//===================================================
void ZDataSourceManager::zh_reviseDefaultUser()
{
    QString statement = QString("SELECT * FROM users WHERE name = \"%1\"").arg(zv_default_user_name);
    QSqlQuery query;

    if(!query.exec(statement))
    {
        QString msg = tr("The SQL statement \"%1\" has been executed with error: \"%2\"!").arg(statement, query.lastError().text());
        QMessageBox::warning(nullptr, tr("SQL Error"), msg, QMessageBox::Ok);
        return;
    }

    if(query.next() && query.value(1).toString() == zv_default_user_name)
    {
        qDebug() << query.value(0) << query.value(1) ;
        return;
    }

    // create default user
    statement = "INSERT INTO users (id, name) VALUES (:id, :name)";
    if(!query.prepare(statement))
    {
        QString msg = tr("The SQL statement \"%1\" has been executed with error: \"%2\"!").arg(statement, query.lastError().text());
        QMessageBox::warning(nullptr, tr("SQL Error"), msg, QMessageBox::Ok);
        return;
    }

    query.bindValue(":id", 0);
    query.bindValue(":name", zv_default_user_name);
    if(!query.exec())
    {
        QString msg = tr("The SQL statement \"%1\" has been executed with error: \"%2\"!").arg(statement, query.lastError().text());
        QMessageBox::warning(nullptr, tr("SQL Error"), msg, QMessageBox::Ok);

    }
}
//===================================================
void ZDataSourceManager::zp_createNewTask()
{
    int taskNum = zh_findNextTaskNum();

    int row = zv_taskModel->rowCount();
    zv_taskModel->insertRows(row, 1);
    zv_taskModel->setData(zv_taskModel->index(row, 1),  tr("Task %1").arg(QString::number(taskNum)));
    zv_taskModel->setData(zv_taskModel->index(row, 2),  "");
    zv_taskModel->setData(zv_taskModel->index(row, 3),  splitByStringMap.value(SPLIT_LINE_BY::WORD));
    zv_taskModel->setData(zv_taskModel->index(row, 4),  outputOrderStringMap.value(OUTPUT_ORDER::RANDOM));
    zv_taskModel->setData(zv_taskModel->index(row, 5),  lineEndKeyStringMap.value(LINE_END_KEY::AUTO));
    zv_taskModel->setData(zv_taskModel->index(row, 6),  true);

    zv_taskModel->submitAll();

}
//===================================================
int ZDataSourceManager::zh_findNextTaskNum() const
{
    QSqlQuery query;
    QString statement = "SELECT name FROM tasks";
    if(!query.exec(statement))
    {
        QString msg = tr("Error query execution. \nError: %1").arg(query.lastError().text());
        QMessageBox::warning(nullptr, tr("Error"), msg, QMessageBox:: Ok);
        return 0;
    }

    int maxNum = 0;
    static QRegularExpression re("^(Task)(\\s{0,})(?<number>\\d+)$");
    QRegularExpressionMatch match;
    while(query.next())
    {
        match = re.match(query.value(0).toString().trimmed());
        if(!match.hasMatch())
        {
            continue;
        }

        maxNum = std::max(match.captured("number").toInt(), maxNum);
    }

    return maxNum + 1;
}
//===================================================
void ZDataSourceManager::zp_deleteTasks(QVector<int> rows)
{
    std::sort(rows.begin(), rows.end());
    for(int i = rows.count() - 1;  i >= 0; --i)
    {
        zv_taskModel->removeRows(rows.at(i), 1);
    }

    zv_taskModel->submitAll();
    zv_taskModel->select();
}
//===================================================
ZTask ZDataSourceManager::zp_taskForRow(int row) const
{
    QSqlRecord record = zv_taskModel->record(row);

    if(record.isEmpty())
    {
        return ZTask();
    }

    ZTask task;
    std::get<0>(task) = record.value(1).toString().toStdString();
    std::get<1>(task) = record.value(2).toString().toStdString();
    std::get<2>(task) = splitByStringMap.key(record.value(3).toString());
    std::get<3>(task) = outputOrderStringMap.key(record.value(4).toString());
    std::get<4>(task) = lineEndKeyStringMap.key(record.value(5).toString());
    std::get<5>(task) = record.value(6).toBool();

    return task;
}
//===================================================



