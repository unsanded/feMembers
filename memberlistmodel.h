#ifndef MEMBERLISTMODEL_H
#define MEMBERLISTMODEL_H

#include <QObject>
#include <QSqlTableModel>
#include <QSqlError>
#include <QDebug>
class MemberlistModel : public QSqlTableModel
{
  Q_OBJECT
private:
        QVector<Qt::CheckState> checkedStatus;
        QString searchString;
        bool    exMembersVisible;
public:
  Qt::ItemFlags flags(const QModelIndex &index) const;
  explicit MemberlistModel( QSqlDatabase db, QObject *parent = 0);
  QVariant data(const QModelIndex &idx, int role) const;
  bool setData(const QModelIndex &index, const QVariant &value, int role);
signals:
  
public slots:
  void setExMembersVisible(bool visible);
  void setSearch(QString search);
};

#endif // MEMBERLISTMODEL_H
