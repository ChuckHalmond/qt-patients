#ifndef AUTHDIALOG_H
#define AUTHDIALOG_H

#include "Model/AuthInfo.h"

#include <QDialog>
#include <QString>

namespace Ui {
    class AuthDialog;
}

class AuthDialog : public QDialog
{
    Q_OBJECT

    private:
        Ui::AuthDialog *ui;

    public:
        explicit AuthDialog(QWidget *parent = 0);
        ~AuthDialog();

        QString getUsername() const;
        QString getPassword() const;
        void setUsername(QString username);
        void setPassword(QString password);

        void clearPassword();

    private slots:
        void on_tryAuthButton_clicked();
        void on_exitAuthButton_clicked();

    signals:
        void signal_trigger_tryAuth(const AuthInfo &authInfo);
        void signal_trigger_exitAuth();
};

#endif // AUTHDIALOG_H
