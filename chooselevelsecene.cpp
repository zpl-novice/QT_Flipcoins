#include "chooselevelsecene.h"
#include<QMenu>
#include<QMenuBar>
#include<QPainter>
#include"mypushbutton.h"
#include"playscene.h"
#include<QLabel>
#include<QDebug>
chooselevelsecene::chooselevelsecene(QWidget *parent) : QMainWindow(parent)
{
    //配置选择关卡场景
    resize(380,588);
    //设置标题
    setWindowTitle("选择关卡");
    //创建菜单栏
    QMenuBar * bar = this->menuBar();
    this->setMenuBar(bar);
    //创建开始菜单
    QMenu * startMenu = bar->addMenu("开始");
    //创建按钮菜单项
    QAction * quitAction = startMenu->addAction("退出");
     //点击退出 退出游戏
    connect(quitAction,&QAction::triggered,[=](){this->close();});

    //返回按钮
    backbutton = new MyPushButton(":/BackButton.png",":/BackButtonSelected.png");
    backbutton->setParent(this);
    backbutton->move(this->width()-backbutton->width(),this->height()-backbutton->height());
    //实现返回功能
    connect(backbutton,&MyPushButton::clicked,[=](){
            this->hide();
            //触发自定义信号，关闭自身，该信号写到 signals下做声明
            emit this->chooseSceneBack();
             }
        );

    //创建关卡按钮
    for(int i=0;i<20;i++)
    {
        MyPushButton * menuBtn = new MyPushButton(":/LevelIcon.png");
               menuBtn->setParent(this);
        menuBtn->move(60+(i%4)*70,130+(i/4)*70);
        //按钮上显示的文字
        QLabel * label = new QLabel;
        label->setParent(this);
        label->setFixedSize(menuBtn->width(),menuBtn->height());
        label->setText(QString::number(i+1));
        //设置居中
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        label->move(60+(i%4)*70,130+(i/4)*70);
        //鼠标事件穿透(按钮被label挡住)
        label->setAttribute(Qt::WA_TransparentForMouseEvents,true);
        //监听每个按钮的点击事件
        connect(menuBtn,&MyPushButton::clicked,[=]()
        {
            if(pscene == NULL)  //游戏场景不复用，直接移除掉换新的
            {
                 this->hide();
                 //将点击的关卡号送给playsecen场景
                 pscene = new playscene(i+1);
                  pscene->show();
                  //监听关卡场景的自定义信号，接收到以后显示自身
                  connect(pscene,&playscene::pSceneBack,[=](){
                      this->show();
                      delete  pscene;
                      pscene = NULL;
                  }
                  );
                  connect(pscene,&playscene::levelsignal,this,&chooselevelsecene::myslot);
            }
        });
    }
}
void chooselevelsecene::paintEvent(QPaintEvent *)
{
    //创建画家，指定绘图设备
    QPainter painter(this);
    //创建QPixmap对象
    QPixmap pix;
    //加载图片
    pix.load(":/OtherSceneBg.png");
    //绘制背景图
    painter.drawPixmap(0,0,this->width(),this->height(),pix);


    //加载标题
    pix.load(":/Title.png");

    //绘制标题
    painter.drawPixmap( (this->width() - pix.width())*0.5,30,pix.width(),pix.height(),pix);
}
void chooselevelsecene::myslot(int a)
{
    //qDebug()<<a;
    emit levelsignal(a);
}

