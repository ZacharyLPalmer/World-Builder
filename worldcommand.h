//--------------------------------------------------------------
// File:   worldcommand.h
// Author: Zachary Palmer  Login: zpalm466  Class: CpS 209
// Desc:   This is the header for the file contains the code for
//         execution and undoing of WorldCommands
//--------------------------------------------------------------

#ifndef WORLDCOMMAND_H
#define WORLDCOMMAND_H

#include <string>
#include <vector>

#include "worldobj.h"

using namespace std;

// An abstract command class
class WorldCommand
{
public:

    // abstract method to carry out this command; returns true on success
    virtual WorldObject *execute() = 0;

    virtual ~WorldCommand() { }

    virtual void undo() { }

    virtual void redo() { }
};

// A command class that creates a WorldObject
class CreateCommand: public WorldCommand
{
    int oldID; //old id to use when rolling back an undo
    string type;  // type of object to create
    string image; // image for new object

public:
    CreateCommand(string initType, string initImage):
        type(initType), image(initImage) { }

    //getter method
    int getOldID() { return oldID; }

    //setter method
    void setOldID( int id ) { oldID = id; }

    // creates a WorldObject using data in instance variables
    WorldObject *execute();

    ~CreateCommand() { }

    void undo();

    void redo();
};

class MoveCommand: public WorldCommand
{
    int id;       //id of object to move
    int x, y, oldx, oldy; //position for the object to move

public:
    MoveCommand(int initID, int initRow, int initCol):
        id(initID), x(initRow), y(initCol) { }

    //Getter methods
    int getOldX() { return oldx; }
    int getOldY() { return oldy; }
    int getID() { return id; }

    //Setter Methods
    void setOldX( int x ) { oldx = x; }
    void setOldY( int y ) { oldy = y; }

    //Moves a WorldObject using data in instance variables
    WorldObject* execute();
    //Undos a MoveCommand
    void undo();

    void redo();

    ~MoveCommand() { }
};

class DestroyCommand: public WorldCommand
{
    int id; //id of object to destroy
    string oldtype, oldimage;
    int oldx, oldy;
public:
    DestroyCommand(int initID):
        id(initID) { }

    //Getter methods
    int getOldX() { return oldx; }
    int getOldY() { return oldy; }
    int getID() { return id; }
    string getOldType() { return oldtype; }
    string getOldImage() { return oldimage; }

    //Setter Methods
    void setOldX( int x ) { oldx = x; }
    void setOldY( int y ) { oldy = y; }
    void setOldId( int oldid ) { id = oldid; }
    void setOldImage( string oi ) { oldimage = oi; }
    void setOldtype( string ot ) { oldtype = ot; }

    //destroy a WorldObject using data in instance variables
    WorldObject* execute();

    void undo();

    void redo();

    ~DestroyCommand() {}
};


class UndoManager {
    static UndoManager* instance_;

public:
    vector<WorldCommand*> history;
    vector<WorldCommand*> future;

    WorldObject* doCommand(WorldCommand *cmd);

    bool undo();

    bool redo();

    WorldCommand *getLastHistory();

    WorldCommand *getLastFuture();

    static UndoManager& instance();

};

#endif // WORLDCOMMAND_H
