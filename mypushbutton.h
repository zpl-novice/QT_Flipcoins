#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>
#include<QMouseEvent>
class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit MyPushButton(QPushButton *parent = nullptr);
    //normalImg 代表正常显示的图片
    //pressImg  代表按下后显示的图片，默认为空
    //重载构造函数
     MyPushButton(QString normalImg,QString pressImg = "");

     QString normalImgPath;  //默认显示图片路径
     QString pressedImgPath; //按下后显示图片路径
    void mouseReleaseEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
signals:

};

#endif // MYPUSHBUTTON_H
