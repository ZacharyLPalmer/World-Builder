#include <QLabel>
#include <QPixmap>
#include <iostream>
#include <QTimer>
#include "moveable.h"
#include "worldcommand.h"
#include "world.h"
#include "worldobj.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QTimer *timer = new QTimer(this);
        timer->setInterval(100);
        connect(timer, SIGNAL(timeout()), this, SLOT(timerHit()));
        timer->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

string MainWindow::getType()
{
    if(ui->BasicBtn->isChecked())
    {
        return "ba";
    } else if (ui->WandererBtn->isChecked())
    {
        return "wa";
    } else
    {
        return "tr";
    }
}

void MainWindow::doPrint() {
    vector<WorldObject*>& objects = World::instance().getObjects();

    cout << "\n\tObjects in world:\n" << endl;
    for (WorldObject *obj : objects) {
        cout << obj->toString() << endl;
    }
    cout << endl;
}
void MainWindow::createMovableLabel(string file, string type)
{
    QPixmap label (file.c_str());
    MovableLabel *lbl = new MovableLabel(ui->background);
    connect(lbl,SIGNAL(clicked()),this,SLOT(on_Obj_clicked()));
    WorldCommand *wcmd = new CreateCommand(getType(), type);
    lbl->setWorObj(UndoManager::instance().doCommand(wcmd));
    UndoManager::instance().history.push_back(wcmd);
    ui->MoveBtn->setChecked(false);
    lbl->setPixmap(label);
    lbl->setGeometry(0,0,50,50);
    lbl->setScaledContents(true);
    lbl->show();
    doPrint();
    World::instance().labels.push_back(lbl);
}

void MainWindow::on_RobotBtn_clicked()
{
    createMovableLabel(":images/robot.png","robot");
}

void MainWindow::on_BombBtn_clicked()
{
    createMovableLabel(":/images/bomb.png","bomb");
}

void MainWindow::on_WallBtn_clicked()
{
    createMovableLabel(":/images/wall.png","wall");
}

void MainWindow::on_MoveBtn_clicked()
{
    ui->DeleteBtn->setChecked(false);
    for (size_t i = 0; i < World::instance().labels.size(); i++)
    {
        World::instance().labels[i]->setMDrag(false);
        World::instance().labels[i]->setTrack(true);
    }

}

void MainWindow::on_DeleteBtn_clicked()
{
    ui->MoveBtn->setChecked(false);
    for (size_t i = 0; i < World::instance().labels.size(); i++)
    {
        World::instance().labels[i]->setMDrag(false);
        World::instance().labels[i]->setTrack(false);
    }
}

void MainWindow::on_Obj_clicked()
{

    WorldCommand *wcmd;
    QObject *del = this->sender();
    MovableLabel *lbl = dynamic_cast<MovableLabel*>(del);
    if(ui->DeleteBtn->isChecked())
    {
        wcmd = new DestroyCommand(lbl->getWorObj()->getId());
    } else if (ui->MoveBtn->isChecked())
    {
        wcmd = new MoveCommand(lbl->getWorObj()->getId(),lbl->x(),lbl->y());
    }
    UndoManager::instance().doCommand(wcmd);
    UndoManager::instance().history.push_back(wcmd);
    doPrint();
    if(ui->DeleteBtn->isChecked())
    {
        delete lbl;
        lbl = nullptr;
        for (size_t i = 0; i < World::instance().labels.size(); i++)
        {
            if(World::instance().labels[i] == nullptr)
            {
               World::instance().labels.erase(World::instance().labels.begin()+i);
            }
        }
    }
}


void MainWindow::timerHit()
{
    if(ui->AnimateBtn->isChecked())
    {
        for (size_t i = 0; i < World::instance().labels.size(); i++)
        {
            World::instance().labels[i]->getWorObj()->updatePosition(World::instance().labels[i]);
        }
    }
}


void MainWindow::on_AnimateBtn_clicked()
{
    doPrint();
}



void MainWindow::on_UndoBtn_clicked()
{

}
