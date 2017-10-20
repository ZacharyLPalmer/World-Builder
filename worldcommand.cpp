
#include <iostream>

#include "worldcommand.h"
#include "world.h"

using namespace std;

WorldObject* CreateCommand::execute()
{
    WorldObject *obj = World::instance().createObject(type);
        obj->setImage(image);
        World::instance().add(obj);
        setOldID(obj->getId());
        cout << "\t-> Created id " << obj->getId() << endl;
        return obj;
}

void CreateCommand::undo()
{
    CreateCommand *cmd = dynamic_cast<CreateCommand*>(this);
    WorldObject *obj = World::instance().World::destroy(cmd->getOldID());
    if (obj != NULL) {
        cout << "\t-> Undo Create Successful " << getOldID() << endl;
    } else {
        cout << "\t** Undo Create Unsuccesful " << getOldID() << endl;
        delete obj;
    }
}

void CreateCommand::redo()
{
    WorldObject::decrNID();
    WorldObject *obj = World::instance().createObject(type);
    obj->setImage(image);
    World::instance().add(obj);
    setOldID(obj->getId());
    cout << "\t-> Redone creation of id " << obj->getId() << endl;
}

WorldObject* DestroyCommand::execute()
{
    WorldObject *obj = World::instance().getById(id);
        setOldImage(obj->getImage());
        setOldtype(obj->getType());
        setOldX(obj->getX());
        setOldY(obj->getY());
        setOldId(obj->getId());
        obj = World::instance().World::destroy(id);
        cout << "\t-> Destroyed object " << id << endl;
        return obj;
}

void DestroyCommand::undo()
{
    DestroyCommand *cmd = dynamic_cast<DestroyCommand*>(this);
    WorldObject *obj = World::instance().createObject(cmd->getOldType());
    obj->decrNID();
    obj->setImage(getOldImage());
    obj->setX(getOldX());
    obj->setY(getOldY());
    obj->setId(getID());
    World::instance().add(obj,getID());
    cout << "\t-> Undo Destroy Successful " << getID() << endl;
}

void DestroyCommand::redo()
{
    WorldObject *obj = World::instance().getById(id);
    setOldImage(obj->getImage());
    setOldtype(obj->getType());
    setOldX(obj->getX());
    setOldY(obj->getY());
    setOldId(obj->getId());
    obj = World::instance().World::destroy(id);
    cout << "\t-> Redone destroy " << id << endl;
}

WorldObject *MoveCommand::execute()
{
    WorldObject *obj = World::instance().getById(id);
        setOldX(obj->getX());
        setOldY(obj->getY());
        obj->setX(x);
        obj->setY(y);
        cout << "\t-> Moved object to " << x << "," << y << endl;
        return obj;
}

void MoveCommand::undo()
{
    MoveCommand *cmd = dynamic_cast<MoveCommand*>(this);
    WorldObject *obj = World::instance().getById(cmd->getID());
    obj->setX(getOldX());
    obj->setY(getOldY());
    cout << "\t-> Move undone, new location: " << getOldX() << "," << getOldY() << endl;
}

void MoveCommand::redo()
{
    WorldObject *obj = World::instance().getById(id);
    setOldX(obj->getX());
    setOldY(obj->getY());
    obj->setX(x);
    obj->setY(y);
    cout << "\t-> redone move of object to " << x << "," << y << endl;
}


WorldObject* UndoManager::doCommand(WorldCommand *cmd)
{
    return cmd->execute();
}

WorldCommand* UndoManager::getLastHistory()
{
    if (history.size() > 0)
    {
        WorldCommand* cmd = history[history.size()-1];
        history.pop_back();
        future.push_back(cmd);
        return cmd;
    }
    cout << "\t-> no more commands to undo" << endl;
    return NULL;
}

WorldCommand* UndoManager::getLastFuture()
{
    if (future.size() > 0)
    {
        WorldCommand* cmd = future[future.size()-1];
        future.pop_back();
        history.push_back(cmd);
        return cmd;
    }
    return NULL;
}

bool UndoManager::undo()
{
    WorldCommand* cmd = UndoManager::getLastHistory();
    if (cmd != NULL)
    {
        cmd->undo();
        return true;
    }
    return false;
}

bool UndoManager::redo()
{
    WorldCommand* cmd = UndoManager::getLastFuture();
    if (cmd != NULL)
    {
        cmd->redo();
        return true;
    }
    return false;
}

UndoManager* UndoManager::instance_ = nullptr;

UndoManager& UndoManager::instance() {
    if (instance_ == nullptr) {
        instance_ = new UndoManager();
    }
    return *instance_;
}


