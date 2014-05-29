#include "memberdelegate.h"

MemberDelegate::MemberDelegate(QObject *parent) :
  QItemDelegate(parent)
{
}

void MemberDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
  return QItemDelegate::paint(painter, option, index);
}

QWidget *MemberDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

        int dataType = index.data( DataTypeRole).toInt();
        QWidget* returnWidget;
        if(dataType==Date)
        {
            QString dateString = index.data(Qt::DisplayRole).toString();
            QDate date = QDate::fromString(dateString, "yyyy-MM-dd");
            if(!date.isValid())
              returnWidget = new QDateEdit(parent);
            else
              returnWidget = new QDateEdit(date, parent);
            returnWidget->setProperty("MemberListType", QVariant(Date));
            return returnWidget;
          }
         else if (dataType==Bool){
            returnWidget = new QCheckBox();
            returnWidget->setProperty("MemberListType", QVariant(Bool));
          }
        return QItemDelegate::createEditor(parent, option, index);
}

void MemberDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
        if(editor->property("MemberListType")==Date){
            QDate date = ((QDateEdit*) editor)->date();
            model->setData(index, date.toString("yyyy-MM-dd"));
          }
}
