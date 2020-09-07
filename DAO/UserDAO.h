#ifndef USERDAO_H
#define USERDAO_H

#include <Model/User.h>
#include "ResourceDAO.h"

class UserDAO
{
    private:
        ResourceDAO *resourceDAO;

    public:
        UserDAO();
        ~UserDAO();

        User get(int id);
        QList<User> getList();

        bool add(User user);

        User getFromResourceId(int resourceId);
        bool exists(QString login, QString password);
        int getNextId();

        bool remove(int id);
        bool update(User user);
};

#endif // USERDAO_H
