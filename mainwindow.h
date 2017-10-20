#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <vector>
#include "moveable.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{

    Q_OBJECT


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void createMovableLabel(std::string file, std::string type);

    void on_RobotBtn_clicked();

    void on_BombBtn_clicked();

    void on_WallBtn_clicked();

    std::string getType();

    void doPrint();

    void on_MoveBtn_clicked();

    void on_DeleteBtn_clicked();

    void on_Obj_clicked();

    void on_AnimateBtn_clicked();

    void on_UndoBtn_clicked();

    void timerHit();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
