#ifndef MEMBERLIST_H
#define MEMBERLIST_H

#include <QMainWindow>
#include <QMessageBox>
#include "memberlistmodel.h"
#include "databaseconnection.h"

namespace Ui {
class MemberList;
}

class MemberListWindow : public QMainWindow
{
    Q_OBJECT
    
        MemberlistModel model;
        QMessageBox verifySaveBox;
public:
    explicit MemberListWindow(DatabaseConnection& db, QWidget *parent = 0);
    ~MemberListWindow();
    
private slots:
        void on_addButton_pressed();

        void save();

        void on_searchButton_pressed();
        void search(QString value);
private:
    Ui::MemberList *ui;
};

#endif // MEMBERLIST_H
