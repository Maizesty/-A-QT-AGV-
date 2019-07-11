#include "mainwindow.h"
#include "ui_mainwindow.h"
int N=31,M=31;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Demo");
    this->resize((N+9)*25,(M+9)*25);
    this->setFocus(Qt::MouseFocusReason);
    mode1=new QRadioButton(this);
    mode1->setText("八方位模式");
    mode1->setGeometry((N+2)*25,250,70,20);
    mode1->setEnabled(true);
    mode1->setChecked(true);
    mode2=new QRadioButton(this);
    mode2->setText("四方位模式");
    mode2->setGeometry((N+2)*25,270,70,20);
    mode2->setEnabled(true);
    mode2->setChecked(false);
    b_set=new QPushButton(this);
    b_set->setText("设置阻碍");
    b_set->setGeometry((N+2)*25,30,70,20);
    b_set->setEnabled(true);
    agv_set=new QPushButton(this);
    agv_set->setText("部署agv");
    agv_set->setGeometry((N+2)*25,60,70,20);
    agv_set->setEnabled(true);
    tg_set=new QPushButton(this);
    tg_set->setText("设定目标");
    tg_set->setGeometry((N+2)*25,90,70,20);
    tg_set->setEnabled(true);
    findpath=new QPushButton(this);
    findpath->setText("寻路");
    findpath->setGeometry((N+2)*25,120,70,20);
    findpath->setEnabled(true);
    refresh1=new QPushButton(this);
    refresh1->setText("重置并\n取消阻碍物");
    refresh1->setGeometry((N+2)*25,150,70,40);
    refresh1->setEnabled(true);
    refresh2=new QPushButton(this);
    refresh2->setText("重置但不\n取消阻碍物");
    refresh2->setGeometry((N+2)*25,200,70,40);
    refresh2->setEnabled(true);
    a=new Astar();
    connect(b_set,SIGNAL(clicked()),this,SLOT(shift_to_b_set_mode()));
    connect(agv_set,SIGNAL(clicked()),this,SLOT(shift_to_agv_set_mode()));
    connect(tg_set,SIGNAL(clicked()),this,SLOT(shift_to_tg_set_mode()));
    connect(findpath,SIGNAL(clicked()),this,SLOT(_findpath()));
    connect(refresh1,SIGNAL(clicked()),this,SLOT(ref1()));
    connect(refresh2,SIGNAL(clicked()),this,SLOT(ref2()));
    connect(mode1,SIGNAL(clicked()),this,SLOT(_mode1()));
    connect(mode2,SIGNAL(clicked()),this,SLOT(_mode2()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::shift_to_b_set_mode()
{mode=0;
    update();
}
void MainWindow::shift_to_agv_set_mode()
{   mode=1;
    update();
}
void MainWindow::shift_to_tg_set_mode()
{mode=2;
     update();
}
void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(Qt::black);
   for(int i=0;i<31;i++)
           for(int j=0;j<31;j++)
           {
                switch(_MAP[i][j])
                    {
                            case 1://画墙壁
                            painter.setBrush(QBrush(Qt::gray,Qt::SolidPattern));
                            painter.drawRect(QRect(i*25,(j+1)*25,25,25));
                            break;
                            case 0://画通路
                            painter.setBrush(QBrush(Qt::white,Qt::SolidPattern));
                            painter.drawRect(QRect(i*25,(j+1)*25,25,25));
                            break;
                            case 2:
                            painter.setBrush(QBrush(Qt::yellow,Qt::SolidPattern));
                            painter.drawRect(QRect(i*25,(j+1)*25,25,25));
                            break;
   }
                if(setstar)
                {
                    painter.setBrush(QBrush(Qt::red,Qt::SolidPattern));
                    painter.drawRect(QRect(_starx*25,(_stary+1)*25,25,25));
                }
                if(settg)
                {
                    painter.setBrush(QBrush(Qt::blue,Qt::SolidPattern));
                    painter.drawRect(QRect(_endx*25,(_endy+1)*25,25,25));
                }
}
}
void MainWindow::mousePressEvent(QMouseEvent* event)
{


    if(event->button()==Qt::LeftButton&&mode==0)
    {
    int j=(event->y())/25-1,i=(event->x())/25;

    _MAP[i][j]=!_MAP[i][j];
    update();
    }
if(event->button()==Qt::LeftButton&&mode==1)
{
    int j=(event->y())/25-1,i=(event->x())/25;
    _starx=i;
    _stary=j;
    setstar=true;
    update();
}
if(event->button()==Qt::LeftButton&&mode==2)
{
    int j=(event->y())/25-1,i=(event->x())/25;
    _endx=i;
    _endy=j;
    settg=true;
    update();
}
}
void MainWindow:: _findpath()
{
    Node *startPos = new Node(_starx,_stary);
    Node *endPos = new Node(_endx,_endy);
    a->search(startPos,endPos);
    draw(a->way);
}
void MainWindow::draw(Node *current)
{
    if (current->father != NULL)
       draw(current->father);
   _MAP[current->x][current->y]=2;
   update();
}
void MainWindow:: ref1()
{
    for (int i=0;i<N;i++)
        for(int j=0;j<M;j++)
        {
            if(_MAP[i][j]==1||_MAP[i][j]==2)
                _MAP[i][j]=0;
        }
    update();
}

void MainWindow:: ref2()
{
    for (int i=0;i<N;i++)
        for(int j=0;j<M;j++)
        {
            if(_MAP[i][j]==2)
                _MAP[i][j]=0;
        }
    update();
}
void  MainWindow::_mode1()
{
    a->mode=true;
}

void  MainWindow::_mode2()
{
    a->mode=false;
}
