#include "memberlist.h"
#include "databaseconnection.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DatabaseConnection db( "members.db", &a);

    MemberListWindow w(db);
    w.show();
    
    return a.exec();
}
