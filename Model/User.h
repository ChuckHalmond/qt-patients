#ifndef USER_H
#define USER_H

#include "Resource.h"

#include <QString>



class User
{
    private:
        int id;
        QString login;
        QString password;
        Resource resource;

    public:
        User();
        ~User();

        int getId() const;
        QString getLogin() const;
        Resource getResource() const;
        QString getPassword() const;

        void setId(int id);
        void setLogin(const QString &login);
        void setPassword(const QString &password);
        void setResource(const Resource &resource);
};

#endif // USER_H
