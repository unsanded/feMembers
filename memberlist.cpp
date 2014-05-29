#include "memberlist.h"
#include "ui_memberlist.h"

MemberListWindow::MemberListWindow(DatabaseConnection& db, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MemberList),
    model(db.db, this)
{
    ui->setupUi(this);
    ui->memberListView->setModel(&model);
    int idindex = model.fieldIndex("id");
    ui->memberListView->hideColumn(idindex);
    verifySaveBox.setText("Save changes to database?");
    verifySaveBox.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel);

    QObject::connect(ui->saveButtoin, SIGNAL(pressed()),
           this, SLOT(save()) );

    connect(ui->searchBox, SIGNAL(textEdited(QString)), this, SLOT(search(QString)));

    connect(ui->exMembersCheckbox, SIGNAL(toggled(bool)), &model, SLOT(setExMembersVisible(bool)));


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
                        qDebug()<< "error saving changes:\n" << model.lastError().text() << "\n" << model.query().lastQuery();
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
        model.setSearch(value);
}

void MemberListWindow::on_saveButtoin_clicked()
{

}

void MemberListWindow::on_actionEmail_triggered()
{

    QClipboard* cb = QApplication::clipboard();
    cb->setText("haha, im in your clipboard");
}
