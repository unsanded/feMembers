#ifndef QMEMBERLISTVIEW_H
#define QMEMBERLISTVIEW_H

#include "memberdelegate.h"
#include <QTableView>
#include <QPainter>
#include <QSqlTableModel>

class QMemberlistView : public QTableView
{
  Q_OBJECT
public:
  explicit QMemberlistView(QWidget *parent = 0);
  
  void paintEvent(QPaintEvent *e);
  void setModel(QAbstractItemModel *model);
protected:

signals:
  
public slots:
  
};

#endif // QMEMBERLISTVIEW_H
