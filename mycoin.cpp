#include "mycoin.h"
#include<QPixmap>
MyCoin::MyCoin(QPushButton *parent) : QPushButton(parent)
{

}
MyCoin::MyCoin(QString btnimg)
{
    QPixmap pix;
    pix.load(btnimg);
    this->setFixedSize( pix.width(), pix.height() );
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));
    //初始化定时器对象
    timer1 = new QTimer(this);
    timer2 = new QTimer(this);

    //监听正面翻反面的信号,翻转金币
    connect(timer1,&QTimer::timeout,[=]()
    {
        QPixmap pixmap;
        QString str = QString(":/Coin000%1.png").arg(this->min++);
        pixmap.load(str);
        this->setFixedSize(pixmap.width(),pixmap.height() );
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pixmap);
        this->setIconSize(QSize(pixmap.width(),pixmap.height()));
        if(this->min > this->max) //如果大于最大值，重置最小值，并停止定时器
        {
             this->min = 1;
             isdoing=false;   //停止作动画
             timer1->stop();
        }
    });
    //监听反面翻正面的信号,翻转金币
    connect(timer2,&QTimer::timeout,[=]()
    {
        QPixmap pixmap;
        QString str = QString(":/Coin000%1.png").arg((this->max)--);
        pixmap.load(str);
        this->setFixedSize(pixmap.width(),pixmap.height() );
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pixmap);
        this->setIconSize(QSize(pixmap.width(),pixmap.height()));
        if(this->max < this->min) //如果小于最小值，重置最大值，并停止定时器
        {
             this->max = 8;
            isdoing=false;   //停止作动画
             timer2->stop();
        }
    });
}
void MyCoin::changeflag()
{
    //正面翻反面
    if(this->flag==1)
    {
        timer1->start(80);
        isdoing=true;   //开始作动画
        this->flag=false;
    }
    //反面翻正面
    else
    {
        timer2->start(80);
        isdoing=true;   //开始作动画
        this->flag=true;
    }
}
void MyCoin::mousePressEvent(QMouseEvent *e)
{
    if(this->isdoing==true || this->iswin == true )
    {
        return;
    }
    else
    {
        return QPushButton::mousePressEvent(e);
    }
}

