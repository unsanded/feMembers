#ifndef MEMBERLISTMODEL_H
#define MEMBERLISTMODEL_H

#include "member.h"

#include <QObject>
#include <QSqlTableModel>
#include <QSqlError>
#include <QDebug>
#include <QBrush>
#include <QMap>

#define DATEFORMAT "yyyy-MM-dd"

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

        int maxId;

        /**make a brush for drawing the background of a row*/
        QBrush makeBackground(int row) const;
        /**make a brush for drawing the Foreground of a row*/
        QBrush makeForeground(int row) const;
public:
  Qt::ItemFlags flags(const QModelIndex &index) const;
  explicit MemberlistModel( QSqlDatabase db, QObject *parent = 0);
  QVariant data(const QModelIndex &idx, int role) const;
  bool setData(const QModelIndex &index, const QVariant &value, int role);

  //export the selected members as a csv string with only the named fields
  QString exportCsv(const QStringList &list);
  QString exportEmail();


  virtual bool updateRowInTable(int row, const QSqlRecord &values);
 QVariant headerData(int section, Qt::Orientation orientation, int role) const;
  int getId(const QModelIndex &index) const;
  int getId(const int row) const;
signals:
  
public slots:
  void addMember(const Member &member);
  void setExMembersVisible(bool visible); void setSearch(QString search);
  void onUpdate(int row, QSqlRecord& record);
  void selectAll();
  void clearSelection();
};

#endif // MEMBERLISTMODEL_H
