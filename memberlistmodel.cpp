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
        //setHeaderData(0, Qt::Horizontal, tr("Name"));


}
