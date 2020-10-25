#ifndef PLAYSCENE_H
#define PLAYSCENE_H
#include<QSound>
#include <QMainWindow>
#include"mycoin.h"
#include"mypushbutton.h"
class playscene : public QMainWindow
{
    Q_OBJECT
public:
    explicit playscene(QWidget *parent = nullptr);
    playscene(int index);
    void paintEvent(QPaintEvent *);
signals:
    void pSceneBack();
    void levelsignal(int);  //发送过关关卡信号
private:
    int levelindex;
     MyPushButton *backbutton;
     //二维数组,维护关卡数据
     int gameArray[4][4];
     //二维数组，维护金币
     MyCoin * coinArray[4][4];
     bool iswin;
};

#endif // PLAYSCENE_H
