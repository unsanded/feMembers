#include "member.h"
#include "memberlistmodel.h"

#include <QtSql>

MemberlistModel::MemberlistModel( QSqlDatabase db, QObject *parent) :
 QSqlTableModel(parent, db)
{

        QSqlTableModel::setTable("members");
        qDebug() << "setTable() returned \n" << lastError().text();
        setEditStrategy(QSqlTableModel::OnFieldChange);
        setExMembersVisible(true);
        if(select()){
                qDebug() << "update data succesfull\n";
        }
        maxId=0;
        for(int row=0; row<rowCount(); row++){
            int id=getId(createIndex(row, 0));
            if(id>maxId)
              maxId=id;
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

        setExMembersVisible(false);
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
        {
          if(value.toInt()!=Qt::Checked){
            QSqlTableModel::setData(createIndex(index.row(), fieldIndex("dateLeft")), QDate::currentDate().toString(DATEFORMAT), Qt::EditRole);
            return QSqlTableModel::setData(index, 0);
        }
        else
        {
          return QSqlTableModel::setData(index, 1);
        }
      }
      return QSqlTableModel::setData(index, value, role);
}

QString MemberlistModel::exportCsv(const QStringList &list)
{
  QString result;
  for(int i=0; i<rowCount(); i++){
      QString line;
      QString comma;
      if(checkedStatus[getId(createIndex(i, 0))]!=Qt::Checked)
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
QString MemberlistModel::exportEmail()
{
  QString result;
  QString comma;
  for(int i=0; i<rowCount(); i++){
      if(checkedStatus[getId(createIndex(i, 0))]!=Qt::Checked)
        continue;
      QString email=data(createIndex(i, fieldIndex("email")), Qt::DisplayRole).toString();
      QString firstname=data(createIndex(i, fieldIndex("firstName")), Qt::DisplayRole).toString();
      QString lastname=data(createIndex(i, fieldIndex("lastName")), Qt::DisplayRole).toString();
      result.append(comma);
      result.append(QString("\"%1 %2\"<%3>").arg(firstname).arg(lastname).arg(email));
      comma=",";
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

int MemberlistModel::getId(const int row) const
{
  int idColumn=fieldIndex("id");
  return QSqlTableModel::data(createIndex(row, idColumn), Qt::DisplayRole).toInt();
}

void MemberlistModel::addMember(const Member &member)
{
  int row = rowCount();
  QSqlRecord newRecord;

  newRecord.append(QSqlField("id",  QVariant::Int ));
  newRecord.append(QSqlField("firstName",  QVariant::String ));
  newRecord.append(QSqlField("lastName",  QVariant::String ));
  newRecord.append(QSqlField("scNumber",  QVariant::String ));
  newRecord.append(QSqlField("studentNumber",  QVariant::String ));
  newRecord.append(QSqlField("bDate",  QVariant::Date ));
  newRecord.append(QSqlField("email",  QVariant::String ));
  newRecord.append(QSqlField("phone",  QVariant::String ));
  newRecord.append(QSqlField("street",  QVariant::String ));
  newRecord.append(QSqlField("houseNumber",  QVariant::String ));
  newRecord.append(QSqlField("postalCode",  QVariant::String ));
  newRecord.append(QSqlField("city",  QVariant::String ));
  newRecord.append(QSqlField("country",  QVariant::String ));
  newRecord.append(QSqlField("nationality",  QVariant::String ));
  newRecord.append(QSqlField("gender",  QVariant::Bool ));
  newRecord.append(QSqlField("currentlyMember",  QVariant::Bool ));
  newRecord.append(QSqlField("dateLeft",  QVariant::Date ));
  newRecord.append(QSqlField("dateJoined",  QVariant::Date ));
  newRecord.append(QSqlField("initials",  QVariant::String ));
  newRecord.append(QSqlField("comments",  QVariant::String ));


 newRecord.setValue("id", QVariant(++maxId));
 newRecord.setValue("firstName", QVariant(member.firstName));
 newRecord.setValue("lastName", QVariant(member.lastName));
 newRecord.setValue("scNumber", QVariant(member.sportscardNumber));
 newRecord.setValue("studentNumber", QVariant(member.studentNumber));
 newRecord.setValue("bDate", QVariant(member.birthDate));
 newRecord.setValue("email", QVariant(member.email));
 newRecord.setValue("phone", QVariant(member.phoneNumber));
 newRecord.setValue("street", QVariant(member.street));
 newRecord.setValue("houseNumber", QVariant(member.houseNumber));
 newRecord.setValue("postalCode", QVariant(member.postalCode));
 newRecord.setValue("city", QVariant(member.city));
 newRecord.setValue("country", QVariant(member.country));
 newRecord.setValue("nationality", QVariant(member.nationality));
 newRecord.setValue("gender", QVariant(member.gender));
 newRecord.setValue("currentlyMember", QVariant(member.currentlyMember));
 newRecord.setValue("dateLeft", QVariant(member.dateLeft));
 newRecord.setValue("dateJoined", QVariant(member.dateJoined));
 newRecord.setValue("initials", QVariant(member.initials));
 newRecord.setValue("comments", QVariant(member.comments));

 if(!insertRecord(-1, newRecord)){
     qWarning() << "insert failed" << database().lastError();
   }

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
