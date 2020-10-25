#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include<QTimer>
class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    explicit MyCoin(QPushButton *parent = nullptr);
    //传入金币还是银币
    MyCoin(QString btnimg);
    void mousePressEvent(QMouseEvent *e);
    //金币属性
    int posX;    //x坐标
    int posY;    //y坐标
    bool flag;   //正反状态
    int min=1;   //8张图片用于翻转
    int max=8;
    bool isdoing=false; //判断是否动画翻转完成
    bool iswin=false;    //判断是否胜利
    //改变标志
    void  changeflag();
    QTimer *timer1;          //定时器1用于正面翻反面
    QTimer *timer2;          //定时器2用于反面翻正面
signals:
private:


};

#endif // MYCOIN_H
