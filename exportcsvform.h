#ifndef EXPORTCSVFORM_H
#define EXPORTCSVFORM_H

#include <QDialog>

namespace Ui {
  class ExportCsvForm;
}

class ExportCsvForm : public QDialog
{
  Q_OBJECT
  QStringList m_selectedValues;

public:
  explicit ExportCsvForm(QWidget *parent = 0);
  ~ExportCsvForm();

  const QStringList& selectedValues(){
    return m_selectedValues;
  }


private slots:
  void on_putLeft_clicked();


  void on_ExportCsvForm_accepted();

  void on_putRight_clicked();

private:
  Ui::ExportCsvForm *ui;
};

#endif // EXPORTCSVFORM_H
