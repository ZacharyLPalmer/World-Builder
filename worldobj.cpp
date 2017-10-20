//--------------------------------------------------------------
// File:   worldobj.cpp
// Author: Zachary Palmer  Login: zpalm466  Class: CpS 209
// Desc:   This is the file that is used to overide the tostring
//         methods for wanderer and tracker
//--------------------------------------------------------------

#include <string>
#include <sstream>
#include <random>
#include <cmath>
#include <iostream>
#include "mainwindow.h"
#include "worldobj.h"
#include "world.h"


int WorldObject::nextId = 0;

// Simplified helper for "random-int-in-range-A-to-B"
int WorldObject::random_int(int min, int max) {
    static std::default_random_engine engine { std::random_device{}() };
    std::uniform_int_distribution<int> distro{min, max};
    return distro(engine);
}

string Wanderer::toString() {
    stringstream sstrm;
    sstrm << "\t" << id << ": " << x << "," << y << " : " << image << " (wanderer)";
    return sstrm.str();
}

string Tracker::toString() {
    stringstream sstrm;
    sstrm << "\t" << id << ": " << x << "," << y << " : " << image << " (tracker)";
    return sstrm.str();
}

void Wanderer::updatePosition(QLabel *lbl) {
    int i = random_int(-5,5);
    int e = random_int(-5,5);
    this->setX(this->getX()+i);
    this->setY(this->getY()+e);
    lbl->setGeometry(QRect(this->getX()+i,this->getY()+e,50,50));
}

void Tracker::updatePosition(QLabel *lbl)
{
    int closestX = 100000;
    int closestY = 100000;
    WorldObject* target;
    for (size_t i = 0; i < World::instance().labels.size(); i++)
    {
        if(World::instance().labels[i]->getWorObj()->getType() == "wanderer")
        {
            int x = std::abs(this->getX() - World::instance().labels[i]->getWorObj()->getX());
            int y = std::abs(this->getY() - World::instance().labels[i]->getWorObj()->getY());

            if (x < closestX && y < closestY)
            {
                closestX = x;
                closestY = y;
                target = World::instance().labels[i]->getWorObj();
            }
        }
    }

    if((target->getX()-this->getX()) > 0)
    {
        this->setX(this->getX()+5);
        lbl->setGeometry(QRect(this->getX()+5,this->getY(),50,50));
    } else {
        this->setX(this->getX()-5);
        lbl->setGeometry(QRect(this->getX()-5,this->getY(),50,50));
    }

    if((target->getY()-this->getY()) > 0)
    {
        this->setY(this->getY()+5);
        lbl->setGeometry(QRect(this->getX(),this->getY()+5,50,50));
    } else {
        this->setY(this->getY()-5);
        lbl->setGeometry(QRect(this->getX(),this->getY()-5,50,50));
    }
}
