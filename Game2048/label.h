#ifndef LABEL_H
#define LABEL_H
#include <QWidget>
#include <QLabel>

class Label : public QLabel
{
    Q_OBJECT
public:
    Label(int x,int y,QWidget *parent=0);
    void setNum(int num);
    ~Label() {}
};

#endif // LABEL_H
