#ifndef MEMBERLIST_H
#define MEMBERLIST_H

#include <QMainWindow>
#include <QMessageBox>
#include <QClipboard>
#include "memberlistmodel.h"
#include "databaseconnection.h"
#include "addmemberdialog.h"

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
        void on_saveButtoin_clicked();

        void on_actionEmail_triggered();

        void on_actionSelect_All_triggered();

        void on_actionCsv_triggered();

private:
    Ui::MemberList *ui;
};

#endif // MEMBERLIST_H
