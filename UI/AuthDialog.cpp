#include "AuthDialog.h"
#include "ui_AuthDialog.h"

#include <iostream>

AuthDialog::AuthDialog(QWidget *parent) : QDialog(parent),
    ui(new Ui::AuthDialog)
{
    ui->setupUi(this);

    setUsername(QString("Admin"));
    setPassword(QString("Password"));
}

AuthDialog::~AuthDialog()
{
    delete ui;
}

void AuthDialog::on_tryAuthButton_clicked()
{
    AuthInfo authInfo = {
        getUsername(),
        getPassword()
    };

    emit signal_trigger_tryAuth(authInfo);
}

void AuthDialog::on_exitAuthButton_clicked()
{
    emit signal_trigger_exitAuth();
}

QString AuthDialog::getUsername() const
{
    return findChild<QLineEdit*>("authUsernameLineEdit")->text();
}

QString AuthDialog::getPassword() const
{
    return findChild<QLineEdit*>("authPasswordLineEdit")->text();
}

void AuthDialog::setUsername(QString username)
{
    findChild<QLineEdit*>("authUsernameLineEdit")->setText(username);
}

void AuthDialog::setPassword(QString password)
{
    findChild<QLineEdit*>("authPasswordLineEdit")->setText(password);
}
