#ifndef RESOURCEDIALOG_H
#define RESOURCEDIALOG_H

#include "Model/Resource.h"
#include "Model/User.h"

#include <QDialog>

namespace Ui {
    class ResourceDialog;
}

class ResourceDialog : public QDialog
{
    Q_OBJECT

    private:
        Ui::ResourceDialog *ui;

    public:
        explicit ResourceDialog(QWidget *parent = 0);
        ~ResourceDialog();

        Resource getResource();
        void setResource(Resource resource);

        User getUser();
        void setUser(User user);

        void initResourceTypeComboBox(QList<QString> resourceTypes);
        void setResourceTypeComboBoxSelection(QString resourceType);
        QString getResourceTypeComboBoxSelection();

        bool selectedResourceTypeIsUser();
        void checkLockUserFields();

        bool hasAnyMandatoryFieldEmpty();
        void alertMandatoryFieldEmpty();

    private slots:
        void on_cancelResourceEditionButton_clicked();
        void on_validateResourceEditionButton_clicked();
        void on_resourceTypeComboBox_activated(const QString &arg1);

signals:
        void signal_trigger_cancelResourceEdition();
        void signal_trigger_validateResourceEdition();
};

#endif // RESOURCEDIALOG_H
