//===================================================
#ifndef ZSQLTABLESTATEMENTS_H
#define ZSQLTABLESTATEMENTS_H
//===================================================
#include <QMap>
#include <QString>
//===================================================
QMap<QString, QString> createSqlTableStatementMap();
QMap<QString, QString> sqlTableStatementMap = createSqlTableStatementMap();
//===================================================
QMap<QString, QString> createSqlTableStatementMap()
{
    QMap<QString, QString> sqlTableStatementMap;
    sqlTableStatementMap.insert("Bambarbia", "12345");
    sqlTableStatementMap.insert("Cirgudu", "6789");
    return sqlTableStatementMap;
}
//===================================================
#endif // ZSQLTABLESTATEMENTS_H
