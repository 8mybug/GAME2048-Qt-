#include "label.h"

Label::Label(int x,int y,QWidget *parent):QLabel(parent)
{
    this->resize(80,80);
    this->move(20+y*80+y*10,140+x*80+x*10);
    this->setStyleSheet("background-color: rgb(0, 255, 127);");

    QFont font;
    font.setFamily(QStringLiteral("Consolas"));
    font.setPointSize(16);
    this->setFont(font);
    this->setAlignment(Qt::AlignCenter);
}

void Label::setNum(int num)
{
    if(num)
    {
        char str[256] = {};
        sprintf(str,"%d",num);
        this->setText(str);
    }
    else
    {
        this->setText("");
    }
}

