#ifndef CHOOSELEVELSECENE_H
#define CHOOSELEVELSECENE_H

#include <QMainWindow>
#include"mypushbutton.h"
#include"playscene.h"
#include<QSound>
class chooselevelsecene : public QMainWindow
{
    Q_OBJECT
public:
    explicit chooselevelsecene(QWidget *parent = nullptr);
    //重写PaintEvent事件
    void paintEvent(QPaintEvent *);
    void myslot(int);
signals:
    //自定义信号
    void chooseSceneBack();
    void levelsignal(int);  //发送过关关卡信号
private:
    MyPushButton *backbutton;
    playscene *pscene = NULL;
};

#endif // CHOOSELEVELSECENE_H
