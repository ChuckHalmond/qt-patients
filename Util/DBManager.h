#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QString>
#include <QSqlDatabase>

class DBManager
{
    private:
        static QString hostName;
        static QString userName;
        static QString password;

        static QSqlDatabase db;
        static int instances;

    public:
        DBManager();

        static bool createDB();

        static bool openDB();
        static bool closeDB();
};

#endif // DBMANAGER_H
