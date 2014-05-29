#ifndef MEMBERLISTMODEL_H
#define MEMBERLISTMODEL_H

#include <QObject>
#include <QSqlTableModel>
#include <QSqlError>
#include <QDebug>
#include <QBrush>
#include <QMap>

enum MemberListRoles{
  DataTypeRole = Qt::UserRole
};

enum MemberListDataTypes{
  Integer,
  String,
  Date,
  Bool
};

class MemberlistModel : public QSqlTableModel
{
  Q_OBJECT
private:
        QMap<int, int> checkedStatus;
        QString searchString;
        bool    exMembersVisible;
        /**make a brush for drawing the background of a row*/
        QBrush makeBackground(int row) const;
        /**make a brush for drawing the Foreground of a row*/
        QBrush makeForeground(int row) const;
public:
  Qt::ItemFlags flags(const QModelIndex &index) const;
  explicit MemberlistModel( QSqlDatabase db, QObject *parent = 0);
  QVariant data(const QModelIndex &idx, int role) const;
  bool setData(const QModelIndex &index, const QVariant &value, int role);


  int getId(const QModelIndex &index) const;
signals:
  
public slots:
  void setExMembersVisible(bool visible);
  void setSearch(QString search);
  void onUpdate(int row, QSqlRecord& record);
};

#endif // MEMBERLISTMODEL_H
