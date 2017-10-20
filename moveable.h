#ifndef MOVABLE_H
#define MOVABLE_H

#include <QWidget>
#include <QLabel>
#include <QMouseEvent>

#include "mainwindow.h"
#include "worldobj.h"

class MovableLabel : public QLabel
{
    Q_OBJECT

    WorldObject* obj;
    bool mouseDragging;
    bool track;
    QPoint offset;

public:
    explicit MovableLabel(QWidget *parent): QLabel(parent) {
        setMouseTracking(true); // enable mouse move events
        mouseDragging = false;
    }
    void mouseMoveEvent(QMouseEvent *ev) {
        if (mouseDragging)
            this->move(mapToParent(ev->pos() - this->offset));
    }

    void mousePressEvent(QMouseEvent *ev) {
        if (track)
        {
        mouseDragging = true;
        }
        offset = ev->pos(); // location where mouse was clicked within the label
    }

    void mouseReleaseEvent(QMouseEvent *) {
        mouseDragging = false;
        emit clicked();
    }

    void setTrack(bool b) {track = b;}

    void setMDrag(bool b) {mouseDragging = b;}

    void setWorObj(WorldObject* wo) {obj = wo;}

    WorldObject* getWorObj() { return obj; }
signals:
    void clicked();

};

#endif // MOVEABLE_H
