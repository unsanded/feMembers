#include "databaseconnection.h"

DatabaseConnection::DatabaseConnection (QString file, QObject* parent): QObject(parent)
{
        db=QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(file);
        if(db.open()){
                qDebug() << "opened succesfully :D";
        }
        else
        {
                qDebug()<< "database failed to open:\n" << db.lastError().text();
        }
}
