#include "ResourceDialog.h"
#include "ui_ResourceDialog.h"

#include "Util/Tools.h"

#include <QMessageBox>
#include <iostream>

ResourceDialog::ResourceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResourceDialog)
{
    ui->setupUi(this);
}

ResourceDialog::~ResourceDialog()
{
    delete ui;
}

Resource ResourceDialog::getResource()
{
    Resource resource;

    resource.setFirstname(toTitleCase(findChild<QLineEdit*>("resourceFirstnameLineEdit")->text()));
    resource.setName(toTitleCase(findChild<QLineEdit*>("resourceNameLineEdit")->text()));
    resource.setId(findChild<QLineEdit*>("resourceIdLineEdit")->text().toInt());

    return resource;
}

User ResourceDialog::getUser()
{
    User user;

    user.setLogin(findChild<QLineEdit*>("userLoginLineEdit")->text());
    user.setPassword(findChild<QLineEdit*>("userPasswordLineEdit")->text());

    return user;
}

void ResourceDialog::setResource(Resource resource)
{
    findChild<QLineEdit*>("resourceFirstnameLineEdit")->setText(resource.getFirstname());
    findChild<QLineEdit*>("resourceNameLineEdit")->setText(resource.getName());
    findChild<QLineEdit*>("resourceIdLineEdit")->setText(QString::number(resource.getId()));
}

void ResourceDialog::initResourceTypeComboBox(QList<QString> resourceTypes)
{
    findChild<QComboBox*>("resourceTypeComboBox")->clear();
    findChild<QComboBox*>("resourceTypeComboBox")->addItems(resourceTypes);
}

void ResourceDialog::setResourceTypeComboBoxSelection(QString resourceType)
{
    findChild<QComboBox*>("resourceTypeComboBox")->setCurrentIndex(findChild<QComboBox*>("resourceTypeComboBox")->findText(resourceType));
    checkLockUserFields();
}

QString ResourceDialog::getResourceTypeComboBoxSelection()
{
    return findChild<QComboBox*>("resourceTypeComboBox")->itemText(findChild<QComboBox*>("resourceTypeComboBox")->currentIndex());
}

void ResourceDialog::setUser(User user)
{
    findChild<QLineEdit*>("userLoginLineEdit")->setText(user.getLogin());
    findChild<QLineEdit*>("userPasswordLineEdit")->setText(user.getPassword());
}

void ResourceDialog::checkLockUserFields()
{
    if (selectedResourceTypeIsUser())
    {
        findChild<QLineEdit*>("userLoginLineEdit")->setEnabled(true);
        findChild<QLineEdit*>("userPasswordLineEdit")->setEnabled(true);
    }
    else
    {
        findChild<QLineEdit*>("userLoginLineEdit")->setEnabled(false);
        findChild<QLineEdit*>("userPasswordLineEdit")->setEnabled(false);
    }
}

bool ResourceDialog::selectedResourceTypeIsUser()
{
    QString resourceType = getResourceTypeComboBoxSelection();

    return (resourceType.compare("Informaticien") == 0);
}

bool ResourceDialog::hasAnyMandatoryFieldEmpty()
{
    return
        isEmpty(findChild<QLineEdit*>("resourceFirstnameLineEdit")->text())
        || isEmpty(findChild<QLineEdit*>("resourceNameLineEdit")->text())
        || (
                selectedResourceTypeIsUser()
                && (
                    isEmpty(findChild<QLineEdit*>("userLoginLineEdit")->text())
                    || isEmpty(findChild<QLineEdit*>("userPasswordLineEdit")->text())
                )
        );
}

void ResourceDialog::alertMandatoryFieldEmpty()
{
    QMessageBox msgBox;
    msgBox.setText("Action impossible, un champ obligatoire (*) n'a pas été renseigné");
    msgBox.exec();
}

void ResourceDialog::on_cancelResourceEditionButton_clicked()
{
    emit signal_trigger_cancelResourceEdition();
}

void ResourceDialog::on_validateResourceEditionButton_clicked()
{
    if (hasAnyMandatoryFieldEmpty())
    {
        alertMandatoryFieldEmpty();
    }
    else
    {
        emit signal_trigger_validateResourceEdition();
    }
}

void ResourceDialog::on_resourceTypeComboBox_activated(const QString &arg1)
{
    (void)arg1; // In order to silent the compiler -Wunused-parameter warning

    checkLockUserFields();
}
