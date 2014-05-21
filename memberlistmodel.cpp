#include "memberlistmodel.h"

MemberlistModel::MemberlistModel( QSqlDatabase db, QObject *parent) :
 QSqlTableModel(parent, db)
{

        QSqlTableModel::setTable("members");
        qDebug() << "setTable() returned \n" << lastError().text();
        setEditStrategy(QSqlTableModel::OnManualSubmit);
        if(select()){
                qDebug() << "update data succesfull";
        }
        checkedStatus.resize(rowCount());
        //insertColumn(0);
        setHeaderData(0, Qt::Horizontal, QString(" "));

        //translate some fieldnames
        setHeaderData(fieldIndex("firstName"), Qt::Horizontal, tr("first name"));
        setHeaderData(fieldIndex("lastName"), Qt::Horizontal, tr("last name"));
        setHeaderData(fieldIndex("scNumber"), Qt::Horizontal, tr("sportcard number"));
        setHeaderData(fieldIndex("studentNumber"), Qt::Horizontal, tr("student number"));
        setHeaderData(fieldIndex("houseNumber"), Qt::Horizontal, tr("house number"));
        setHeaderData(fieldIndex("postalCode"), Qt::Horizontal, tr("postal code"));
        setHeaderData(fieldIndex("bDate"), Qt::Horizontal, tr("date of birth"));


}

QVariant MemberlistModel::data(const QModelIndex &idx, int role) const
{
        if(idx.column()==0){
                if(role==Qt::CheckStateRole){
                        return checkedStatus[idx.row()];
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
                if(index.row()>=checkedStatus.size())
                        checkedStatus.resize(rowCount());
                //int id=data
                checkedStatus[index.row()]=value.toBool()?Qt::Checked:Qt::Unchecked;
                emit dataChanged(index, index);
                return true;
        }
        return QSqlTableModel::setData(index, value, role);
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
        QString filter = "(firstName LIKE '%" + value + "%' OR lastName LIKE '%" + value + "%')";
        if(!exMembersVisible)
                filter += " AND (currentlyMember = 1)";

        setFilter(filter);
}
