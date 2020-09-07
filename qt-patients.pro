#-------------------------------------------------
#
# Project created by QtCreator 2019-02-08T14:08:12
#
#-------------------------------------------------

QT +=\
    core gui declarative \
    sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qt-patients
TEMPLATE = app


SOURCES +=\
    Main.cpp \
    Application.cpp \
    Controller/MainController.cpp \
    Controller/PatientController.cpp \
    Controller/ResourceController.cpp \
    DAO/PatientDAO.cpp \
    DAO/ResourceDAO.cpp \
    Model/Patient.cpp \
    Model/Resource.cpp \
    Model/ResourceType.cpp \
    UI/MainWindow.cpp \
    Util/DBManager.cpp \
    Controller/AuthController.cpp \
    UI/AuthDialog.cpp \
    Model/PatientSearchTableModel.cpp \
    UI/PatientDialog.cpp \
    DAO/ResourceTypeDAO.cpp \
    UI/ResourceDialog.cpp \
    Util/Tools.cpp \
    Model/ResourcesListModel.cpp \
    Controller/PlanningController.cpp \
    Model/Planning.cpp \
    Model/Consultation.cpp \
    DAO/ConsultationDAO.cpp \
	DAO/UserDAO.cpp \
    Model/User.cpp \
    Model/ResourceTreeItem.cpp \
    Model/ResourceTreeModel.cpp \
    UI/LearnAboutDialog.cpp

HEADERS  += \
    Application.h \
    Controller/MainController.h \
    Controller/PatientController.h \
    Controller/ResourceController.h \
    DAO/PatientDAO.h \
    DAO/ResourceDAO.h \
    Model/Patient.h \
    Model/PatientSearchInfo.h \
    Model/Resource.h \
    Model/ResourceType.h \
    UI/MainWindow.h \
    Util/Constants.h \
    Util/DBManager.h \
    Model/AuthInfo.h \
    Controller/AuthController.h \
    UI/AuthDialog.h \
    Model/PatientSearchTableModel.h \
    UI/PatientDialog.h \
    DAO/ResourceTypeDAO.h \
    UI/ResourceDialog.h \
    Util/Tools.h \
    Model/ResourcesListModel.h \
    Controller/PlanningController.h \
    Model/Planning.h \
    Model/PlanningInfo.h \
    Model/Consultation.h \
    DAO/ConsultationDAO.h \
    DAO/UserDAO.h \
    Model/User.h \
    Model/ResourceTreeItem.h \
    Model/ResourceTreeModel.h \
    UI/LearnAboutDialog.h

FORMS    += \
    UI/MainWindow.ui \
    UI/AuthDialog.ui \
    UI/PatientDialog.ui \
	UI/ResourceDialog.ui \
    UI/LearnAboutDialog.ui
