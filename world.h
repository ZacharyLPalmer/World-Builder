//--------------------------------------------------------------
// File:   world.h
// Author: Zachary Palmer  Login: zpalm466  Class: CpS 209
// Desc:   This is the header file for the file that defines the
//         singleton based world class
//--------------------------------------------------------------

#ifndef WORLD_H
#define WORLD_H

#include <string>
#include <vector>

#include "worldobj.h"
#include "worldcommand.h"
#include "moveable.h"

using namespace std;

class World {
    vector<WorldObject*> objects;

    static World* instance_;

public:
    World() { }

    vector<MovableLabel*> labels;

    //creates a new object in the world
    WorldObject *createObject(const string& type);

    // adds <obj> to objects in world
    void add(WorldObject *obj) {
        objects.push_back(obj);
    }

    // adds back <obj> into the world
    void add(WorldObject *obj, int id);


    // returns object with <id>, or NULL if none
    WorldObject *getById(int id);

    //return the vecotr of <worldobjects>
    vector<WorldObject*>& getObjects() { return objects; }

    // Removes object with <id> from objects and returns it, or returns NULL if not found
    WorldObject *destroy(int id);

    // Resets world
    void reset();

    // Destroy objects
    ~World();

    //world singleton
    static World& instance();

};

//world singlton
World& instance();
extern World world;

#endif // WORLD_H
