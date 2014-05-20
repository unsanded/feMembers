#include "memberlist.h"
#include "ui_memberlist.h"

MemberListWindow::MemberListWindow(DatabaseConnection& db, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MemberList),
    model(db.db, this)
{
    ui->setupUi(this);
    ui->memberListView->setModel(&model);
    verifySaveBox.setText("Save changes to database?");
    verifySaveBox.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel);
    //s
    QObject::connect(ui->saveButtoin, SIGNAL(pressed()),
           this, SLOT(save()) );

    connect(ui->searchBox, SIGNAL(textEdited(QString)), this, SLOT(search(QString)));



}

MemberListWindow::~MemberListWindow()
{
    delete ui;
}

void MemberListWindow::on_addButton_pressed()
{
    model.insertRow(model.rowCount());
}

void MemberListWindow::save()
{
        if(verifySaveBox.exec()==QMessageBox::Save){
                if(!model.submitAll()){
                        qDebug()<< "error saving changes:\n" << model.lastError().text();
                }
        }
}

void MemberListWindow::on_searchButton_pressed()
{
    QString searchValue=ui->searchBox->text();
    search(searchValue);
}


void MemberListWindow::search(QString value)
{
        model.setFilter("firstName LIKE '%" + value + "%' OR lastName LIKE '%" + value + "%'");
}
