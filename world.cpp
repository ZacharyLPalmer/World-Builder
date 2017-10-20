//--------------------------------------------------------------
// File:   world.cpp
// Author: Zachary Palmer  Login: zpalm466  Class: CpS 209
// Desc:   This is the file that defines the singleton based
//         world class
//--------------------------------------------------------------

#include "world.h"

// returns object with <id>, or NULL if none
WorldObject *World::getById(int id) {
    for (size_t i = 0; i < objects.size(); ++i) {
        WorldObject *obj = objects.at(i);
        if (obj->getId() == id) {
            return obj;
        }
    }
    return NULL;
}


WorldObject *World::destroy(int id)
{
    WorldObject *obj = NULL;
    for (size_t i = 0; i < objects.size(); i++)
    {
        if (objects[i]->getId() == id)
        {
            obj = objects[i];
            objects.erase(objects.begin()+i);
        }
    }
    return obj;
}

void World::reset()
{
    WorldObject::setNextID(0);
    for (size_t i = 0; i < objects.size(); i++)
    {
        delete objects[i];
    }
    objects.clear();
}

World::~World()
{
    for (size_t i = 0; i < objects.size(); i++)
    {
        delete objects[i];
    }
}

// factory: creates and returns a WorldObject or derived class, determined by
// <type>. Returns NULL if <type> is not recognized.
WorldObject *World::createObject(const string& type) {
    if (type.find("ba") == 0)
        return new WorldObject;
    else if (type.find("tr") == 0)
        return new Tracker;
    else if (type.find("wa") == 0)
        return new Wanderer;
    else
        return NULL;
}

void World::add(WorldObject *obj, int id)
{
    for (int i = 0; i < objects.size(); i++)
    {
        if (objects[i]->getId() > id)
        {
            objects.insert(objects.begin() + (i),obj);
            return;
        }
    }
    objects.push_back(obj);
}



World* World::instance_ = nullptr;

World& World::instance() {
    if (instance_ == nullptr) {
        instance_ = new World();
    }
    return *instance_;
}
