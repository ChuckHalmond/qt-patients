#include "Application.h"
#include "Util/DBManager.h"

#include <iostream>

Application::Application(int argc, char *argv[]) :
    QApplication(argc, argv),
    mainController(NULL),
    authController(new AuthController())
{
    init();
}

Application::~Application()
{
    finalize();

    if (authController != NULL) {
        delete authController;
        authController = NULL;
    }

    if (mainController != NULL) {
        delete mainController;
        mainController = NULL;
    }
}

void Application::init()
{
    createDB();

    initAuthController();
}

void Application::finalize()
{
    if (authController != NULL)
        finalizeAuthController();

    if (mainController != NULL)
        finalizeMainController();
}

void Application::createDB()
{
    DBManager::createDB();
}

void Application::destroyDB()
{
}

/* Authentication controller*/

void Application::initAuthController()
{
    // Do connections
    QObject::connect(authController, SIGNAL(signal_trigger_validateAuth()), this, SLOT(slot_handle_validateAuth()));
    QObject::connect(authController, SIGNAL(signal_trigger_leaveAuth()), this, SLOT(slot_handle_leaveAuth()));
}

void Application::finalizeAuthController()
{
    // Undo connections
    QObject::disconnect(authController, SIGNAL(signal_trigger_validateAuth()));
    QObject::disconnect(authController, SIGNAL(signal_trigger_leaveAuth()));
}

/* Main controller*/

void Application::initMainController()
{
    // Do connections
    QObject::connect(mainController, SIGNAL(signal_forward_quit()), this, SLOT(slot_handle_quit()));
}

void Application::finalizeMainController()
{
    // Undo connections
    QObject::disconnect(mainController, SIGNAL(signal_forward_quit()));
}

void Application::slot_handle_validateAuth()
{
    finalizeAuthController();

    delete authController;
    authController = NULL;

    mainController = new MainController();

    initMainController();
}

void Application::slot_handle_leaveAuth()
{
    quit();
}

void Application::slot_handle_quit()
{
    quit();
}
