#ifndef APPLICATION_H
#define APPLICATION_H

#include "Controller/MainController.h"
#include "Controller/AuthController.h"

#include <QApplication>

class Application : public QApplication
{
    Q_OBJECT

    private:
        MainController* mainController;
        AuthController* authController;

    public:
        explicit Application(int argc, char *argv[]);
        ~Application();

        void init();
        void finalize();

        // DB
        void createDB();
        void destroyDB();

        // AuthController
        void createAuthController();
        void initAuthController();
        void finalizeAuthController();
        void destroyAuthController();

        // MainController
        void createMainController();
        void initMainController();
        void finalizeMainController();
        void destroyMainController();

    public slots:

        // From authController
        void slot_handle_validateAuth();
        void slot_handle_leaveAuth();

        // From mainController
        void slot_handle_quit();

};

#endif // APPLICATION_H
