#include "ResourceController.h"
#include "Model/ResourceTreeItem.h"

#include <QMenu>
#include <QStringList>
#include <QVariant>

#include <iostream>

/* Constructor & destructor */

ResourceController::ResourceController(QTreeView *resourcesTreeView) :
    resourceDAO(new ResourceDAO),
    resourceTypeDAO(new ResourceTypeDAO),
    userDAO(new UserDAO()),
    resourceDialog(new ResourceDialog()),
    resourcesTreeView(resourcesTreeView)
{
    createTreeView();

    init();
}

ResourceController::~ResourceController()
{
    finalize();

    destroyTreeView();

    delete resourceTreeModel;
    resourceTreeModel = NULL;

    resourcesTreeView = NULL;

    delete resourceDialog;
    resourceDialog = NULL;

    delete resourceTypeDAO;
    resourceTypeDAO = NULL;

    delete userDAO;
    userDAO = NULL;

    delete resourceDAO;
    resourceDAO = NULL;
}

void ResourceController::init()
{
    QObject::connect(resourceDialog, SIGNAL(signal_trigger_validateResourceEdition()), this, SLOT(slot_handle_validateResourceEdition()));
    QObject::connect(resourceDialog, SIGNAL(signal_trigger_cancelResourceEdition()), this, SLOT(slot_handle_cancelResourceEdition()));
}

void ResourceController::finalize()
{
    QObject::disconnect(resourceDialog, SIGNAL(signal_trigger_validateResourceEdition()));
    QObject::disconnect(resourceDialog, SIGNAL(signal_trigger_cancelResourceEdition()));
}

void ResourceController::createTreeView()
{
    QList<QString> headers;
    headers.append("Resource");
    QString data = QStringList(resourceTypeDAO->getLabelsList()).join('\n');

    resourceTreeModel = new ResourceTreeModel(headers, data);

    QList<ResourceType> types = resourceTypeDAO->getList();
    for (int i = 0; i < types.size(); i++)
    {
        QList<Resource> resources = resourceDAO->getListFromTypeId(types.at(i).getId());
        for (int j = 0; j < resources.size(); j++)
        {
            Resource resource = resources.at(j);
            QModelIndex index = resourceTreeModel->index(i, 0, QModelIndex());

            if (!resourceTreeModel->insertRow(0, index))
                return;

            QModelIndex item = resourceTreeModel->index(0, 0, index);
            QString itemData = QString("%1\t\t%2\t\t%3").arg(resource.getId()).arg(resource.getFirstname()).arg(resource.getName());
            resourceTreeModel->setData(item, QVariant(itemData));
         }
    }

    resourcesTreeView->setModel(resourceTreeModel);
}

void ResourceController::destroyTreeView()
{
    delete resourceTreeModel;
    resourceTreeModel = NULL;
}

void ResourceController::slot_handle_displayTreeViewContextMenu(const QPoint &pos)
{
    (void)pos; // In order to silent the compiler -Wunused-parameter warning

    ResourceTreeItem *item = resourceTreeModel->getItem(resourcesTreeView->selectionModel()->currentIndex());

    if (item->parent() != resourceTreeModel->getRootItem())
    {
        QMenu contextMenu;

        QAction editResource("Éditer", this);
        QAction deleteResource("Supprimer", this);

        int resourceId = item->data(0).toString().split('\t')[0].toInt();

        // Embed the id of the selected resource in the action data
        editResource.setData(
            resourceId
        );
        deleteResource.setData(
            resourceId
        );

        QObject::connect(&editResource, SIGNAL(triggered()), this, SLOT(slot_handle_editExistingResource()));
        QObject::connect(&deleteResource, SIGNAL(triggered()), this, SLOT(slot_handle_deleteResource()));

        contextMenu.addAction(&editResource);
        contextMenu.addAction(&deleteResource);

        contextMenu.exec(QCursor::pos());
    }
}

void ResourceController::slot_handle_editNewResource()
{
    Resource resource;
    int resourceId = resourceDAO->getNextId();
    QList<QString> resourceTypesLabels = resourceTypeDAO->getLabelsList();
    resource.setId(resourceId);

    resourceDialog->initResourceTypeComboBox(resourceTypesLabels);
    resourceDialog->setResourceTypeComboBoxSelection(resourceTypesLabels.at(0));
    resourceDialog->setResource(resource);
    resourceDialog->show();

    emit signal_trigger_updateStatusBarMessage("Édition d'une nouvelle fiche ressource..");
}

void ResourceController::slot_handle_editExistingResource(/*const int &resourceId*/)
{
    // Retrieves the resource id from the action data
    QAction *action = qobject_cast<QAction *>(sender());
    int resourceId = action->data().toInt();
    Resource resource = resourceDAO->get(resourceId);
    User user = userDAO->getFromResourceId(resourceId);

    resourceDialog->setResource(resource);
    resourceDialog->setUser(user);
    resourceDialog->initResourceTypeComboBox(resourceTypeDAO->getLabelsList());
    resourceDialog->setResourceTypeComboBoxSelection(resource.getType().getLabel());
    resourceDialog->show();

    emit signal_trigger_updateStatusBarMessage("Édition d'une fiche ressource existante..");
}

void ResourceController::slot_handle_validateResourceEdition()
{
    Resource resource = resourceDialog->getResource();
    resource.setType(resourceTypeDAO->getByLabel(resourceDialog->getResourceTypeComboBoxSelection()));

    User user = resourceDialog->getUser();
    user.setResource(resource);

    // Check if a user already exists for this resource
    int userId = userDAO->getFromResourceId(resource.getId()).getId();

    if (resourceDialog->selectedResourceTypeIsUser())
    {
        if (userId > 0)
        {
            user.setId(userId);
            userDAO->update(user);
        }
        else
        {
            user.setId(userDAO->getNextId());
            userDAO->add(user);
        }
    }

    if (resourceDAO->contains(resource.getId()))
    {
        resourceDAO->update(resource);

        // We remove the old row from the TreeView
        resourceTreeModel->removeRow(resourcesTreeView->selectionModel()->currentIndex().row(), resourcesTreeView->selectionModel()->currentIndex().parent());
    }
    else
    {
        resourceDAO->add(resource);
    }

    // We add the new row to the TreeView
    resourceDialog->hide();
    QList<ResourceType> types = resourceTypeDAO->getList();
    ResourceType type;
    for (int i = 0; i < types.size(); i++)
    {
        type = types.at(i);
        if (resource.getType().getId() == type.getId())
        {
            QModelIndex index = resourceTreeModel->index(i, 0, QModelIndex());

            if (!resourceTreeModel->insertRow(0, index))
                return;

            QModelIndex item = resourceTreeModel->index(0, 0, index);
            QString itemData = QString("%1\t\t%2\t\t%3").arg(resource.getId()).arg(resource.getFirstname()).arg(resource.getName());
            resourceTreeModel->setData(item, QVariant(itemData));

            break;
        }
    }

    emit signal_trigger_updateStatusBarMessage("La fiche ressource a bien été enregistrée.");
}

void ResourceController::slot_handle_deleteResource(/*const int &resourceId*/)
{
    // Retrieves the resource id from the action data
    QAction *action = qobject_cast<QAction *>(sender());
    int resourceId = action->data().toInt();

    resourceDAO->remove(resourceId);
    resourceTreeModel->removeRow(resourcesTreeView->selectionModel()->currentIndex().row(), resourcesTreeView->selectionModel()->currentIndex().parent());

    emit signal_trigger_updateStatusBarMessage("La fiche ressource a bien été supprimée.");
}

void ResourceController::slot_handle_cancelResourceEdition()
{
    resourceDialog->hide();
    emit signal_trigger_updateStatusBarMessage("");
}
