//--------------------------------------------------------------
// File:   worldobj.h
// Author: Zachary Palmer  Login: zpalm466  Class: CpS 209
// Desc:   This is the header file that is used to define the
//         world object class and its child classes as well as
//         overiding themethods for wanderer and tracker
//--------------------------------------------------------------

#ifndef WORLDOBJ_H
#define WORLDOBJ_H

#include <string>
#include <sstream>
#include <random>
#include <QLabel>

using namespace std;

// The ancestor of all objects in the world
class WorldObject {
protected:
    int id;
    int x, y;
    string image;
    string type;

    static int nextId;
public:
    WorldObject(int initX, int initY, string initImg):
        x(initX), y(initY), image(initImg) {
        id = ++nextId;
    }

    WorldObject(): x(0), y(0) {
      id = ++nextId;
    }

    // Simplified helper for "random-int-in-range-A-to-B"
    int random_int(int min, int max);

    static void decrNID() { --nextId; }

    // updates entity's position in world
    virtual void updatePosition(QLabel*) { }

    // returns a textual representation of this object
    virtual string toString() {
        stringstream sstrm;
        sstrm << "\t" << id << ": " << x << "," << y << " : " << image;
        return sstrm.str();
    }

    // accessors

    int getId() { return id; }
    int getX() { return x; }
    int getY() { return y; }
    virtual string getType() { return "basic"; }
    string getImage() { return image; }

    // mutators

    void setId(int newId) { id = newId; }
    void setX(int newX) { x = newX; }
    void setY(int newY) { y = newY; }
    void setImage(const string& newImg) { image = newImg; }
    static void setNextID(int newId) { nextId = newId; }


};

// An object that moves randomly about the world
class Wanderer : public WorldObject {

public:
    string toString();
    string getType() { return "wanderer"; }
    void updatePosition(QLabel*);
};


// An object which moves towards a target object
class Tracker : public WorldObject {

public:
    string toString();
    string getType() { return "tracker"; }
    void updatePosition(QLabel*);

};



#endif // WORLDOBJ_H
