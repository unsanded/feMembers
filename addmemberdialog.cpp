#include "addmemberdialog.h"
#include "ui_addmemberdialog.h"

AddMemberDialog::AddMemberDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::AddMemberDialog)
{
  ui->setupUi(this);
}

AddMemberDialog::~AddMemberDialog()
{
  delete ui;
}

Member AddMemberDialog::getMember()
{
  Member result;
  result.firstName=ui->firstname->text();
  result.lastName=ui->name->text();
  result.street=ui->street->text();
  result.houseNumber=ui->houseNumber->text();
  result.postalCode=ui->postalcode->text();
  result.city=ui->city->text();
  result.email=ui->email->text();
  result.studentNumber=ui->studentnumber->text();
  result.gender=ui->gender->text();
  result.initials=ui->initials->text();
  result.birthDate=ui->birthdate->date();
  result.sportscardNumber=ui->sportcardNumber->text();
  result.nationality=ui->nationality->text();
  result.phoneNumber=ui->phone->text();
  return result;
}
