#include "playscene.h"
#include<QMenu>
#include<QMenuBar>
#include<QPainter>
#include<QString>
#include<QLabel>
#include<QFont>
#include"mycoin.h"
#include"dataconfig.h"
#include<QTimer>
#include<QDebug>
#include<QPropertyAnimation>
playscene::playscene(QWidget *parent) : QMainWindow(parent)
{

}
playscene::playscene(int index)
{
    this->levelindex=index;
    //配置选择关卡场景
    resize(380,588);
    //设置标题
    QString str = QString("关卡%1").arg(this->levelindex);
    setWindowTitle(str);
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
            emit this->pSceneBack();
             }
        );

    //右下角当前关卡标题
    QLabel * label = new QLabel;
    label->setParent(this);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    label->setFont(font);
    QString str2 = QString("Leavel: %1").arg(this->levelindex);
    label->setText(str2);
    //设置大小和位置
    label->setGeometry(QRect(20, this->height() - 50,120, 50));

    //初始化二维数组
    dataConfig config;
    for(int i = 0 ; i < 4;i++)
    {
        for(int j = 0 ; j < 4; j++)
        {
            gameArray[i][j]=config.mData[this->levelindex][i][j];
        }
    }
    //创建胜利图片
    QLabel* winLabel = new QLabel;
    QPixmap tmpPix;
    tmpPix.load(":/LevelCompletedDialogBg.png");
    winLabel->setGeometry(0,0,tmpPix.width(),tmpPix.height());
    winLabel->setPixmap(tmpPix);
    winLabel->setParent(this);
    winLabel->move( (this->width() - tmpPix.width())*0.5 , -tmpPix.height());

    //创建金币的背景图片
    for(int i = 0 ; i < 4;i++)
    {
        for(int j = 0 ; j < 4; j++)
        {
           //绘制背景图片
           QLabel* label = new QLabel;
           label->setGeometry(0,0,50,50);
           label->setPixmap(QPixmap(":/BoardNode(1).png"));
           label->setParent(this);
           label->move(80 + i*50,200+j*50);

           //创建金币对象
           QString str;
           if(gameArray[i][j]==1)
           {
               str = ":/Coin0001.png";
           }
           else
           {
               str = ":/Coin0008.png";
           }
           MyCoin * coin = new MyCoin(str);
           coin->setParent(this);
           coin->move(83 + i*50,203+j*50);
           coin->posX=i;   //用下标来表示金币位置
           coin->posY=j;
           coin->flag=this->gameArray[i][j]; //1正面，0反面

           coinArray[i][j]=coin;  //金币二维数组，记录金币
           connect(coin,&MyCoin::clicked,[=]()
           {
               coin->changeflag();   //金币被点击时调用翻转函数
               //翻金币音效
               QSound *flipSound = new QSound(":/ConFlipSound.wav",this);
               flipSound->play();

               this->gameArray[i][j]=this->gameArray[i][j] == 0 ? 1 : 0;
               //数组内部记录的标志同步修改
               //翻周围硬币
               QTimer::singleShot(300, this,[=](){
               if(coin->posX+1<=3)  //右侧金币可以翻转
               {
                   //翻转右侧金币
                   coinArray[coin->posX+1][coin->posY]->changeflag();
                   this->gameArray[coin->posX+1][coin->posY]=this->gameArray[coin->posX+1][coin->posY] == 0 ? 1 : 0;
               }
               if(coin->posX-1>=0)  //左侧金币可以翻转
               {
                   //翻转左侧金币
                   coinArray[coin->posX-1][coin->posY]->changeflag();
                   this->gameArray[coin->posX-1][coin->posY]=this->gameArray[coin->posX-1][coin->posY] == 0 ? 1 : 0;
               }
               if(coin->posY+1<=3)  //上方金币可以翻转
               {
                   //翻转上方金币
                   coinArray[coin->posX][coin->posY+1]->changeflag();
                   this->gameArray[coin->posX][coin->posY+1]=this->gameArray[coin->posX][coin->posY+1] == 0 ? 1 : 0;
               }
               if(coin->posY-1>=0)  //下方金币可以翻转
               {
                   //翻转下方金币
                   coinArray[coin->posX][coin->posY-1]->changeflag();
                   this->gameArray[coin->posX][coin->posY-1]=this->gameArray[coin->posX][coin->posY-1] == 0 ? 1 : 0;
               }

               //判断是否胜利
                this->iswin=true;
               for(int i=0;i<4;i++)
               {
                   for(int j=0;j<4;j++)
                   {
                       if(coinArray[i][j]->flag==0)
                       {
                           iswin=false;
                           break;
                       }
                   }
               }
               if(this->iswin==true)
               {
                  // qDebug()<<" 胜利";
                   //将所有按钮的胜利标志改为true
                   for(int i=0;i<4;i++)
                   {
                       for(int j=0;j<4;j++)
                       {
                           coinArray[i][j]->iswin=true;
                       }
                   }
                   //弹出胜利图片
                   QPropertyAnimation * animation1 =  new QPropertyAnimation(winLabel,"geometry");
                   animation1->setDuration(1000);
                   animation1->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
                   animation1->setEndValue(QRect(winLabel->x(),winLabel->y()+124,winLabel->width(),winLabel->height()));
                   animation1->setEasingCurve(QEasingCurve::OutBounce);
                   animation1->start();
                   //胜利音效
                    QSound *winSound = new QSound(":/LevelWinSound.wav",this);
                    winSound->play();
                    emit this->levelsignal(this->levelindex);
               }
               });
           });
         }
     }
}
void playscene::paintEvent(QPaintEvent *)
{
    //加载背景
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //加载标题
    pix.load(":/Title.png");
    pix = pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap( 10,30,pix.width(),pix.height(),pix);
}

