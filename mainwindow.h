#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <iostream>
#include <QMouseEvent>
#include <QLabel>
#include <QDebug>
#include <QPushButton>
#include <QRadioButton>
#include <cmath>
#include "astar.h"
extern int _MAP[31][31];
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();    
    QPushButton *b_set;
    QPushButton *agv_set;
    QPushButton *tg_set;
    QPushButton *findpath;
    QPushButton *refresh1;
    QPushButton *refresh2;
    QRadioButton *mode1;
    QRadioButton *mode2;
    class Astar *a;
    int mode=0;
    int fpathmode=0;
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent* event);
    int _starx,_stary,_endx,_endy;
    bool setstar=false;
    bool settg=false;
    void draw(Node *current);
private slots:
    void shift_to_b_set_mode();
    void shift_to_agv_set_mode();
    void shift_to_tg_set_mode();
    void _findpath();
    void ref1();
    void ref2();
    void _mode1();
    void _mode2();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
