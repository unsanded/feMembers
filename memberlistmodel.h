#ifndef MEMBERLISTMODEL_H
#define MEMBERLISTMODEL_H

#include <QObject>
#include <QSqlTableModel>
#include <QSqlError>
#include <QDebug>
class MemberlistModel : public QSqlTableModel
{
  Q_OBJECT

public:
  explicit MemberlistModel( QSqlDatabase db, QObject *parent = 0);
  
signals:
  
public slots:
  
};

#endif // MEMBERLISTMODEL_H
