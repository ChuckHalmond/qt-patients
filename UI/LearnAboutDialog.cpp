#include "LearnAboutDialog.h"
#include "ui_LearnAboutDialog.h"

LearnAboutDialog::LearnAboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LearnAboutDialog)
{
    ui->setupUi(this);
}

LearnAboutDialog::~LearnAboutDialog()
{
    delete ui;
}
