#include "qmemberlistview.h"

QMemberlistView::QMemberlistView(QWidget *parent) :
  QTableView(parent)
{
        setItemDelegate(new MemberDelegate(this));
}

void QMemberlistView::paintEvent(QPaintEvent *e)
{
  QTableView::paintEvent(e);
}

void QMemberlistView::setModel(QAbstractItemModel *model)
{
        QTableView::setModel(model);
}
