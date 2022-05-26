//===================================================
#include "X_DataSourceManager.h"
#include "X_SqlTableStatements.h"

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


#include <QStandardItemModel>

//===================================================
//===================================================
X_DataSourceManager::X_DataSourceManager(QObject *parent)
    : X_AbstractTaskSource{parent}
{
    if(!xh_connectToDatabase())
    {
        throw;
    }

    if(!xh_reviseDatabaseTables())
    {
        throw;
    }

    xh_reviseDefaultUser();

    xh_createComponents();
    xh_createConnections();
}
//===================================================
X_DataSourceManager::~X_DataSourceManager()
{
    xv_taskModel->submitAll();

    {
        QSqlDatabase db = QSqlDatabase::database();
       db.close();
    }
    QSqlDatabase::removeDatabase( QSqlDatabase::defaultConnection );
}
//===================================================
QAbstractItemModel* X_DataSourceManager::xp_taskModel() const
{
    return xv_taskModel;
}
//===================================================
bool X_DataSourceManager::xh_connectToDatabase()
{
    QStringList paths = QCoreApplication::libraryPaths();
    paths.append(".");
    paths.append("sqldrivers");
    QCoreApplication::setLibraryPaths(paths);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(xv_databaseName);

    if(!db.open())
    {
        QString msg = tr("Error connecting to database \"%1\". \nError: %2")
                .arg(xv_databaseName, db.lastError().text());
        QMessageBox::critical(nullptr, tr("Database error"), msg, QMessageBox::Ok);
        return false;
    }

    return true;
}
//===================================================
void X_DataSourceManager::xh_createComponents()
{
    xv_taskModel = new QSqlTableModel(this);
    xv_taskModel->setTable("tasks");
    xv_taskModel->setHeaderData(1, Qt::Horizontal,QVariant(tr("Task")));
    xv_taskModel->select();

    xv_statisticsModel = new QStandardItemModel;

}
//===================================================
void X_DataSourceManager::xh_createConnections()
{

}
//===================================================
bool X_DataSourceManager::xh_reviseDatabaseTables()
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
void X_DataSourceManager::xh_reviseDefaultUser()
{
    QString statement = QString("SELECT * FROM users WHERE name = \"%1\"").arg(xv_default_user_name);
    QSqlQuery query;

    if(!query.exec(statement))
    {
        QString msg = tr("The SQL statement \"%1\" has been executed with error: \"%2\"!").arg(statement, query.lastError().text());
        QMessageBox::warning(nullptr, tr("SQL Error"), msg, QMessageBox::Ok);
        return;
    }

    if(query.next() && query.value(1).toString() == xv_default_user_name)
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
    query.bindValue(":name", xv_default_user_name);
    if(!query.exec())
    {
        QString msg = tr("The SQL statement \"%1\" has been executed with error: \"%2\"!").arg(statement, query.lastError().text());
        QMessageBox::warning(nullptr, tr("SQL Error"), msg, QMessageBox::Ok);

    }
}
//===================================================
void X_DataSourceManager::xp_createNewTask()
{
    int taskNum = xh_findNextTaskNum();

    int row = xv_taskModel->rowCount();
    xv_taskModel->insertRows(row, 1);
    xv_taskModel->setData(xv_taskModel->index(row, 1),  tr("Task %1").arg(QString::number(taskNum)));
    xv_taskModel->setData(xv_taskModel->index(row, 2),  "");
    xv_taskModel->setData(xv_taskModel->index(row, 3),  splitByStringMap.value(SPLIT_LINE_BY::WORD));
    xv_taskModel->setData(xv_taskModel->index(row, 4),  outputOrderStringMap.value(OUTPUT_ORDER::RANDOM));
    xv_taskModel->setData(xv_taskModel->index(row, 5),  lineEndKeyStringMap.value(LINE_END_KEY::AUTO));
    xv_taskModel->setData(xv_taskModel->index(row, 6),  true);

    xv_taskModel->submitAll();

}
//===================================================
int X_DataSourceManager::xh_findNextTaskNum() const
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
void X_DataSourceManager::xp_deleteTasks(QVector<int> rows)
{
    std::sort(rows.begin(), rows.end());
    for(int i = rows.count() - 1;  i >= 0; --i)
    {
        xv_taskModel->removeRows(rows.at(i), 1);
    }

    xv_taskModel->submitAll();
    xv_taskModel->select();
}
//===================================================
ZTask X_DataSourceManager::xp_taskForRow(int row) const
{
    QSqlRecord record = xv_taskModel->record(row);

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
QAbstractItemModel* X_DataSourceManager::xp_statisticsModel() const
{
    return xv_statisticsModel;
}
//===================================================
void X_DataSourceManager::xp_loadTaskStatistics(QMap<QString, WordStatistics>& taskStatistics)
{
    xv_statisticsModel->clear();

    foreach(QString word, taskStatistics.keys())
    {
        QStandardItem* item = new QStandardItem(word);
        xv_statisticsModel->appendRow(item);
    }

    qDebug() << "STATISTICS LOADED";
}
//===================================================




