#include "memberlistmodel.h"

MemberlistModel::MemberlistModel( QSqlDatabase db, QObject *parent) :
 QSqlTableModel(parent, db)
{

        QSqlTableModel::setTable("members");
        qDebug() << "setTable() returned \n" << lastError().text();
        setEditStrategy(QSqlTableModel::OnManualSubmit);
        if(select()){
                qDebug() << "update data succesfull\n";
        }
        insertColumn(0);
        setHeaderData(0, Qt::Horizontal, QString(" "));
//*
        //translate some fieldnames
        setHeaderData(fieldIndex("firstName"), Qt::Horizontal, tr("first name"));
        setHeaderData(fieldIndex("lastName"), Qt::Horizontal, tr("last name"));
        setHeaderData(fieldIndex("scNumber"), Qt::Horizontal, tr("sportcard number"));
        setHeaderData(fieldIndex("studentNumber"), Qt::Horizontal, tr("student number"));
        setHeaderData(fieldIndex("houseNumber"), Qt::Horizontal, tr("house number"));
        setHeaderData(fieldIndex("postalCode"), Qt::Horizontal, tr("postal code"));
        setHeaderData(fieldIndex("bDate"), Qt::Horizontal, tr("date of birth"));
//*/

}

QVariant MemberlistModel::data(const QModelIndex &idx, int role) const
{
        if(role==Qt::BackgroundRole || role==Qt::BackgroundColorRole){
          return makeBackground(idx.row());
        }
        else if (role==Qt::ForegroundRole)
          return makeForeground(idx.row());
        else if (role==DataTypeRole){
          if(idx.column()==fieldIndex("bDate"))
            return Date;
          if(idx.column()==fieldIndex("dateJoined"))
            return Date;
          if(idx.column()==fieldIndex("dateLeft"))
            return Date;
          if(idx.column()==fieldIndex("currentlyMember"))
            return Bool;
          else return String;
        }

        if(idx.column()==0){//checkbox column
          int retval;
          switch(role)
          {
          case Qt::CheckStateRole:
          case Qt::DisplayRole:
                  retval =getId(idx);
                  retval = checkedStatus[retval];
                  return retval;
            case DataTypeRole:
              return Bool;

          default: return QVariant();
          }
        }
        else
        {
                return QSqlTableModel::data(idx, role);
        }

}

bool MemberlistModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
        if(index.column()==0){
                int id=getId(index);
                int v=value.toInt();
                checkedStatus[id]=value.toInt();
                emit dataChanged(index, index);
                return true;
        }
        return QSqlTableModel::setData(index, value, role);
}

int MemberlistModel::getId(const QModelIndex &index) const
{
  int idColumn=fieldIndex("id");
  return QSqlTableModel::data(createIndex(index.row(), idColumn), Qt::DisplayRole).toInt();
}

void MemberlistModel::setExMembersVisible(bool visible)
{
exMembersVisible=visible;
setSearch(searchString);
}


Qt::ItemFlags MemberlistModel::flags(const QModelIndex &index) const
{
        if(index.column()==0)
                return QSqlTableModel::flags(index) | Qt::ItemIsUserCheckable;
        return QSqlTableModel::flags(index);
}


void MemberlistModel::setSearch(QString value)
{
        searchString=value;
        QString filter = "(firstName LIKE '%" + searchString + "%' OR lastName LIKE '%" + searchString + "%')";
        if(!exMembersVisible)
                filter += " AND (currentlyMember = 1)";

        setFilter(filter);
}

void MemberlistModel::onUpdate(int row, QSqlRecord &record)
{
}

QBrush MemberlistModel::makeBackground(int row) const
{
  QBrush result(Qt::SolidPattern);
  if(data(createIndex(row, fieldIndex("gender")), Qt::DisplayRole).toString().startsWith('m', Qt::CaseInsensitive))
        result.setColor(QColor(200,200,254));
  else if(data(createIndex(row, fieldIndex("gender")), Qt::DisplayRole).toString().startsWith('f', Qt::CaseInsensitive))
        result.setColor(QColor(254,200,200));
  else
       result.setColor(Qt::white);
       return result;

}

QBrush MemberlistModel::makeForeground(int row) const
{
  int isMember=QSqlTableModel::data(createIndex(row, fieldIndex("currentlyMember"))).toInt();
  if(isMember)
      return QBrush(Qt::black);
  else
      return QBrush(Qt::gray);

}
