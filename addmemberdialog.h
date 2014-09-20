#ifndef ADDMEMBERDIALOG_H
#define ADDMEMBERDIALOG_H

#include "member.h"

#include <QDialog>

namespace Ui {
  class AddMemberDialog;
}

class AddMemberDialog : public QDialog
{
  Q_OBJECT


public:
  explicit AddMemberDialog(QWidget *parent = 0);
  ~AddMemberDialog();
  Member getMember();

private slots:

private:
  Ui::AddMemberDialog *ui;
};

#endif // ADDMEMBERDIALOG_H
