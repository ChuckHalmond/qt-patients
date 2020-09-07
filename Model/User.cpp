#include "User.h"

/* Constructor & destructor */

User::User()
{

}

User::~User()
{

}

/* Getters */

int User::getId() const
{
    return id;
}

QString User::getLogin() const
{
    return login;
}

Resource User::getResource() const
{
    return resource;
}

QString User::getPassword() const
{
    return password;
}

/* Setters */

void User::setId(int id)
{
    this->id = id;
}

void User::setLogin(const QString &login)
{
    this->login = login;
}

void User::setPassword(const QString &password)
{
    this->password = password;
}

void User::setResource(const Resource &resource)
{
    this->resource = resource;
}
