#ifndef MEMBERDELEGATE_H
#define MEMBERDELEGATE_H

#include "memberlistmodel.h"

#include <QItemDelegate>
#include <QSqlTableModel>
#include <QDateEdit>
#include <QCheckBox>
#include <QComboBox>

class MemberDelegate : public QItemDelegate
{
  Q_OBJECT
public:
  explicit MemberDelegate(QObject *parent = 0);
  virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
  virtual QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
  virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
signals:
  
public slots:
  
};

#endif // MEMBERDELEGATE_H
