#include "exportcsvform.h"
#include "ui_exportcsvform.h"

ExportCsvForm::ExportCsvForm(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::ExportCsvForm)
{
  ui->setupUi(this);
  ui->selectedList->addItem("firstName");
  ui->selectedList->addItem("lastName");
  ui->selectedList->addItem("email");
  ui->selectedList->addItem("phone");

  ui->avalableList->addItem("scNumber");
  ui->avalableList->addItem("studentNumber");
  ui->avalableList->addItem("bDate");
  ui->avalableList->addItem("street");
  ui->avalableList->addItem("houseNumber");
  ui->avalableList->addItem("postalCode");
  ui->avalableList->addItem("city");
  ui->avalableList->addItem("nationality");
  ui->avalableList->addItem("gender");
  ui->avalableList->addItem("currentlyMember");
  ui->avalableList->addItem("dateLeft");
  ui->avalableList->addItem("dateJoined");
  ui->avalableList->addItem("initials");
  ui->avalableList->addItem("comments");
}

ExportCsvForm::~ExportCsvForm()
{
  delete ui;
}

void ExportCsvForm::on_putLeft_clicked()
{
      QListWidgetItem* item= ui->avalableList->takeItem(ui->avalableList->currentRow());
      ui->selectedList->addItem(item);
}

void ExportCsvForm::on_ExportCsvForm_accepted()
{
  m_selectedValues.clear();

  for(int i=0; i<ui->selectedList->count(); i++)
    {
      m_selectedValues << ui->selectedList->item(i)->text();
    }
}

void ExportCsvForm::on_putRight_clicked()
{
      QListWidgetItem* item= ui->selectedList->takeItem(ui->selectedList->currentRow());
      ui->avalableList->addItem(item);
}
