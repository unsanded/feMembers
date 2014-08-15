#include "memberlistmodel.h"

MemberlistModel::MemberlistModel( QSqlDatabase db, QObject *parent) :
 QSqlTableModel(parent, db)
{

        QSqlTableModel::setTable("members");
        qDebug() << "setTable() returned \n" << lastError().text();
        setEditStrategy(QSqlTableModel::OnFieldChange);
        setExMembersVisible(false);
        if(select()){
                qDebug() << "update data succesfull\n";
        }
//        insertColumn(0);
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
        if(idx.column()==0 && role==Qt::CheckStateRole){//checkbox column
          int retval;
          retval =getId(idx);
          retval = checkedStatus[retval];
          return retval;
        }
        else if (idx.column()==0 && role==Qt::DisplayRole){
            return QVariant("");
          }
        else if (role==Qt::ForegroundRole)
          if(idx.column()==0)
            return QBrush();
          else
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

        if(idx.column()==fieldIndex("currentlyMember") && role== Qt::CheckStateRole){
            return (QSqlTableModel::data(idx).toInt()?Qt::Checked:Qt::Unchecked);
          }
        return QSqlTableModel::data(idx, role);

}

bool MemberlistModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
        if(index.column()==0 && role==Qt::CheckStateRole){
                int id=getId(index);
                int v=value.toInt();
                checkedStatus[id]=value.toInt();
                emit dataChanged(index, index);
                return true;
        }
        if(index.column()==fieldIndex("currentlyMember") && role == Qt::CheckStateRole)
          return QSqlTableModel::setData(index, value==Qt::Checked);
        return QSqlTableModel::setData(index, value, role);
}

QString MemberlistModel::exportCsv(const QStringList &list)
{
  QString result;
  for(int i=0; i<rowCount(); i++){
      QString line;
      QString comma;
      if(!data(createIndex(i, 0), Qt::DisplayRole).toInt()==0)
        continue;

      for(int j=0; j< list.count(); j++){
          QString field=data(createIndex(i, fieldIndex(list[j])), Qt::DisplayRole).toString();
          line.append(comma);
          line.append(QString("\"%1\"").arg(field));
          comma=",";
        }
      result.append(line);
      result.append(";\n");
    }
  return result;
}

bool MemberlistModel::updateRowInTable(int row, const QSqlRecord &values)
{
  //int idColumn=fieldIndex("id");
  bool ret = QSqlTableModel::updateRowInTable(row, values);

  return ret;


}

QVariant MemberlistModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  if(role==Qt::DisplayRole && orientation==Qt::Vertical){
      return data(index(section, fieldIndex("firstName")), Qt::DisplayRole);
    }
  return QSqlTableModel::headerData(section, orientation, role);
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
        QString columnName=headerData(index.column(), Qt::Horizontal, Qt::DisplayRole).toString();
        if(index.column()==0)
                return Qt::ItemIsUserCheckable | Qt::ItemIsEditable|Qt::ItemIsSelectable|Qt::ItemNeverHasChildren|Qt::ItemIsEnabled;
        if(columnName=="currentlyMember")
                return Qt::ItemIsUserCheckable | Qt::ItemIsEditable|Qt::ItemIsSelectable|Qt::ItemNeverHasChildren|Qt::ItemIsEnabled;
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

void MemberlistModel::selectAll()
{
  for(int i=0; i<rowCount(); i++)
    setData(index(i, 0), Qt::Checked, Qt::CheckStateRole);
}

void MemberlistModel::clearSelection()
{
  for(int i=0; i<rowCount(); i++)
    setData(index(i, 0), Qt::Unchecked, Qt::CheckStateRole);
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
