#ifndef RESOURCETYPEDAO_H
#define RESOURCETYPEDAO_H

#include "Model/ResourceType.h"

class ResourceTypeDAO
{
    public:
        ResourceTypeDAO();
        ~ResourceTypeDAO();

        ResourceType get(int id);
        QList<ResourceType> getList();
        QList<QString> getLabelsList();
        ResourceType getByLabel(QString label);
};

#endif // RESOURCETYPEDAO_H
