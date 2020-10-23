#ifndef WIDGET2048_H
#define WIDGET2048_H
#include <QWidget>
#include <QKeyEvent>
#include "label.h"

namespace Ui {
class Widget2048;
}

class Widget2048 : public QWidget
{
    Q_OBJECT
    Label* labs[4][4];
    int arr[4][4];
    int score;
    int best;
    bool isMove;
    bool isAlive;
public:
    explicit Widget2048(QWidget *parent = 0);
    ~Widget2048();

    void randNum(void);
    int countNull(void);
    void addScore(int num=0);
    void upDateBest(void);
    void checkAlive(void);

    void keyReleaseEvent(QKeyEvent* event);

    void up(void);
    void down(void);
    void left(void);
    void right(void);

public slots:
    void btn_new_game_slot(void);
private:
    Ui::Widget2048 *ui;
};

#endif // WIDGET2048_H
