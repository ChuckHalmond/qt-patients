#ifndef AUTHCONTROLLER_H
#define AUTHCONTROLLER_H

#include "UI/AuthDialog.h"
#include "DAO/UserDAO.h"

#include <QObject>

class AuthController : public QObject
{
    Q_OBJECT

    private:
        UserDAO *userDAO;
        AuthDialog *authDialog;

    public:
        AuthController();
        ~AuthController();

        void init();
        void finalize();

        bool authInfoIsValid(AuthInfo authInfo);
        void alertWrongAuthInfo();

    public slots:
        void slot_handle_tryAuth(const AuthInfo &authInfo);
        void slot_handle_exitAuth();

    signals:
        void signal_trigger_validateAuth();
        void signal_trigger_leaveAuth();
};

#endif // AUTHCONTROLLER_H
