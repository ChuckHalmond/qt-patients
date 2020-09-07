#ifndef RESOURCEDAO_H
#define RESOURCEDAO_H

#include "Model/Resource.h"
#include "ResourceTypeDAO.h"

class ResourceDAO
{
    private:
        ResourceTypeDAO resourceTypeDAO;

    public:
        ResourceDAO();
        ~ResourceDAO();

        Resource get(int id);
        QList<Resource> getList();

        bool add(Resource resource);
        bool contains(int id);
        bool remove(int id);
        bool update(Resource resource);
        int getNextId();

        QList<Resource> getListFromTypeId(int typeId);
};

#endif // RESOURCEDAO_H
