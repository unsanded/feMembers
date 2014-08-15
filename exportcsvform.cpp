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
}

ExportCsvForm::~ExportCsvForm()
{
  delete ui;
}

void ExportCsvForm::on_putLeft_clicked()
{

}

void ExportCsvForm::on_ExportCsvForm_accepted()
{
  m_selectedValues.clear();

  for(int i=0; i<ui->selectedList->count(); i++)
    {
      m_selectedValues << ui->selectedList->item(i)->text();
    }
}
