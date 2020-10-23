#include <QMessageBox>
#include <fstream>
#include "widget2048.h"
#include "ui_widget2048.h"

using namespace std;

Widget2048::Widget2048(QWidget *parent) :
    QWidget(parent),ui(new Ui::Widget2048),
    best(0),isMove(true),isAlive(true)
{
    ui->setupUi(this);

    for(int x=0; x<4; x++)
    {
        for(int y=0; y<4; y++)
        {
            labs[x][y] = new Label(x,y,this);
            arr[x][y] = 0;
        }
    }

    randNum();

    connect(ui->btn_new_game,SIGNAL(clicked()),this,SLOT(btn_new_game_slot()));

    ifstream ifs("best.dat");
    if(ifs.good())
    {
        ifs >> best;
        ifs.close();
    }
    upDateBest();
    qDebug("%d\n",sizeof(arr));
    ifs.open("score.dat");
    if(ifs.good())
    {
        ifs >> score;
        for(int x=0; x<4; x++)
        {
            for(int y=0; y<4; y++)
            {
                ifs >> arr[x][y];
                labs[x][y]->setNum(arr[x][y]);
            }
        }
        ifs.close();
    }
    addScore();
}

Widget2048::~Widget2048()
{
    delete ui;
    ofstream ofs("best.dat");
    if(ofs.good())
    {
        ofs << best;
        ofs.close();
    }

    if(isAlive)
    {
        ofs.open("score.dat");
        if(ofs.good())
        {
            ofs << score << endl;
            for(int x=0; x<4; x++)
            {
                for(int y=0; y<4; y++)
                {
                    ofs << arr[x][y] << " ";
                }
                ofs << endl;
            }
            ofs.close();
        }
    }
    else
    {
        remove("score.dat");
    }
}

void Widget2048::randNum(void)
{
    if(!isMove || !countNull())
    {
        return;
    }

    while(true)
    {
        int x = rand() % 4;
        int y = rand() % 4;
        if(0 == arr[x][y])
        {
            arr[x][y] = 2;
            labs[x][y]->setNum(arr[x][y]);
            return;
        }
    }

}

int Widget2048::countNull(void)
{
    int null = 0;
    for(int x=0; x<4; x++)
    {
        for(int y=0; y<4; y++)
        {
            if(0 == arr[x][y])
                null++;
        }
    }
    return null;
}

void Widget2048::keyReleaseEvent(QKeyEvent* event)
{
    isMove = false;
    switch(event->key())
    {
    case Qt::Key_Up: up(); break;
    case Qt::Key_Down: down(); break;
    case Qt::Key_Left: left(); break;
    case Qt::Key_Right: right(); break;
    }

    randNum();

    for(int x=0; x<4; x++)
    {
        for(int y=0; y<4; y++)
        {
            labs[x][y]->setNum(arr[x][y]);
        }
    }

    checkAlive();
}

void Widget2048::up()
{
    for(int y=0; y<4; y++)
    {
        int end = 0;
        for(int x=1; x<4; x++)
        {
            for(int i=x; i>0 && end<i; i--)
            {
                if(arr[i][y] == arr[i-1][y] && arr[i][y])
                {
                    end = i;
                    arr[i-1][y] *= 2;
                    arr[i][y] = 0;
                    isMove = true;
                    addScore(arr[i-1][y]);
                }
                else if(arr[i][y] && !arr[i-1][y])
                {
                    arr[i-1][y] = arr[i][y];
                    arr[i][y] = 0;
                    isMove = true;
                }
            }
        }
    }
}

void Widget2048::down()
{
    for(int y=0; y<4; y++)
    {
        int end = 3;
        for(int x=2; x>=0; x--)
        {
            for(int i=x; i<4 && end>i; i++)
            {
                if(arr[i][y] == arr[i+1][y] && arr[i][y])
                {
                    end = i;
                    arr[i+1][y] *= 2;
                    arr[i][y] = 0;
                    isMove = true;
                    addScore(arr[i+1][y]);
                }
                else if(arr[i][y] && !arr[i+1][y])
                {
                    arr[i+1][y] = arr[i][y];
                    arr[i][y] = 0;
                    isMove = true;
                }
            }
        }
    }
}

void Widget2048::left()
{
    for(int x=0; x<4; x++)
    {
        int end = 0;
        for(int y=1; y<4; y++)
        {
            for(int i=y; i>=0 && end<i; i--)
            {
                if(arr[x][i] == arr[x][i-1] && arr[x][i])
                {
                    end = i;
                    arr[x][i-1] *= 2;
                    arr[x][i] = 0;
                    isMove = true;
                    addScore(arr[x][i-1]);
                }
                else if(arr[x][i] && !arr[x][i-1])
                {
                    arr[x][i-1] = arr[x][i];
                    arr[x][i] = 0;
                    isMove = true;
                }
            }
        }
    }
}

void Widget2048::right()
{
    for(int x=0; x<4; x++)
    {
        int end = 3;
        for(int y=2; y>=0; y--)
        {
            for(int i=y; i<4 && end>i; i++)
            {
                if(arr[x][i] == arr[x][i+1] && arr[x][i])
                {
                    arr[x][i+1] *= 2;
                    arr[x][i] = 0;
                    end = i;
                    isMove = true;
                    addScore(arr[x][i+1]);
                }
                else if(arr[x][i] && !arr[x][i+1])
                {
                    arr[x][i+1] = arr[x][i];
                    arr[x][i] = 0;
                    isMove = true;
                }
            }
        }
    }
}

void Widget2048::btn_new_game_slot(void)
{
    for(int x=0; x<4; x++)
    {
        for(int y=0; y<4; y++)
        {
            arr[x][y] = 0;
            labs[x][y]->setNum(arr[x][y]);
        }
    }

    isMove = true;
    randNum();

    score = 0;
    addScore();
}

void Widget2048::addScore(int num)
{
    char str[255] = {};
    score += num;
    sprintf(str,"%d",score);
    ui->lab_score->setText(str);
    if(score > best)
    {
        best = score;
        upDateBest();
    }
}

void Widget2048::upDateBest(void)
{
    char str[255] = {};
    sprintf(str,"%d",best);
    ui->lab_best->setText(str);
}

void Widget2048::checkAlive(void)
{
    if(0 < countNull())
    {
        return;
    }

    for(int x=0; x<4; x++)
    {
        for(int y=0; y<3; y++)
        {
            if(arr[x][y] == arr[x][y+1])
            {
                return;
            }
        }
    }

    for(int y=0; y<4; y++)
    {
        for(int x=0; x<3; x++)
        {
            if(arr[x][y] == arr[x+1][y])
            {
                return;
            }
        }
    }

    isAlive = false;
    QMessageBox::StandardButton stdBtn = QMessageBox::information(this,
                                                                  "Game2048","游戏结束！再来一局吧？",
                                                                  QMessageBox::Yes,
                                                                  QMessageBox::No);
    switch(stdBtn)
    {
    case QMessageBox::Yes: btn_new_game_slot(); break;
    case QMessageBox::No: emit close(); break;
    }

}
