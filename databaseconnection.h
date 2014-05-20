#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H

#include <QtSql/QtSql>
#include <QDebug>

class DatabaseConnection : public QObject{
	Q_OBJECT
	public:
		DatabaseConnection( QString file="members.db", QObject* parent=0);
		QSqlDatabase db;
	private:
		DatabaseConnection(DatabaseConnection& other):QObject(other.parent()){};



};

#endif // DATABASECONNECTION_H
