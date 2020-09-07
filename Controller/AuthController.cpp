#include "AuthController.h"
#include "UI/AuthDialog.h"

#include <QMessageBox>
#include <QPair>

#include <iostream>

AuthController::AuthController() :
    userDAO(new UserDAO()),
    authDialog(new AuthDialog())
{
    init();
}

AuthController::~AuthController()
{
    finalize();

    delete userDAO;
    userDAO = NULL;

    delete authDialog;
    authDialog = NULL;
}

void AuthController::init()
{
    // Do connections
    QObject::connect(authDialog, SIGNAL(signal_trigger_tryAuth(AuthInfo)), this, SLOT(slot_handle_tryAuth(AuthInfo)));
    QObject::connect(authDialog, SIGNAL(signal_trigger_exitAuth()), this, SLOT(slot_handle_exitAuth()));

    // Show ui
    authDialog->show();
}

void AuthController::finalize()
{
    // Close ui
    authDialog->close();

    // Undo connections
    QObject::disconnect(authDialog, SIGNAL(signal_trigger_tryAuth(AuthInfo)));
    QObject::disconnect(authDialog, SIGNAL(signal_trigger_exitAuth()));
}

void AuthController::slot_handle_exitAuth() {
    emit signal_trigger_leaveAuth();
}

void AuthController::slot_handle_tryAuth(const AuthInfo &authInfo) {
    if (authInfoIsValid(authInfo))
    {
        emit signal_trigger_validateAuth();
    }
    else
    {
       alertWrongAuthInfo();
    }
}

void AuthController::alertWrongAuthInfo()
{
    QMessageBox msgBox;
    msgBox.setText("Authentification impossible, veuillez réessayer.");
    msgBox.exec();

    authDialog->setPassword("");
}

bool AuthController::authInfoIsValid(AuthInfo authInfo) {
    return userDAO->exists(authInfo.username, authInfo.password);
}
