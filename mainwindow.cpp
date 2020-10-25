#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QIcon>
#include<QPainter>
#include<QFont>
#include<QSqlDatabase>
#include<QSqlError>
#include<QMessageBox>
#include<QtSql>
#include<QFileInfo>
#include<QSqlQuery>
#include<QDebug>
#include<QTableView>
#include <QtSql/QSqlQueryModel>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->exitaction,&QAction::triggered,this,&QMainWindow::close);
    resize(380,588);
    setWindowTitle("翻金币");
   // setWindowIcon(QIcon(":/Coin0001.png"));
    QFont font("Microsoft YaHei",20,75);
    ui->labeluser->setFont(font);
    ui->labelpassword->setFont(font);
    QFont font2("Microsoft YaHei",5,75);
    ui->label1->setFont(font2);
    ui->lineEditpassword->setEchoMode(QLineEdit::Password);
    //打开数据库
    connectDB();
    //实例化选择关卡场景
    choosescene = new chooselevelsecene;

    //监听选择关卡场景的自定义信号，接收到以后显示自身
    connect(choosescene,&chooselevelsecene::chooseSceneBack,[=](){
        this->show();
    }
    );
    //监听选择关卡场景，接收到以后输出关卡号
    connect(choosescene,&chooselevelsecene::levelsignal,this,&MainWindow::myslot);

    resultview.setParent(this);
    resultview.hide();
    resultview.resize(220,130);
    resultview.move(90,180);
    connect(ui->action,&QAction::triggered,this,&MainWindow::sortslot);
    connect(ui->action_2,&QAction::triggered,this,&MainWindow::sortslot1);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::paintEvent(QPaintEvent *)
{
    //创建画家，指定绘图设备
    QPainter painter(this);
    //创建QPixmap对象
    QPixmap pix;
    //加载图片
    pix.load(":/PlayLevelSceneBg.png");
    //绘制背景图
    painter.drawPixmap(0,0,this->width(),this->height(),pix);


    //加载标题
    pix.load(":/Title.png");
    //缩放图片
    pix = pix.scaled(pix.width()*0.5,pix.height()*0.5);
    //绘制标题
    painter.drawPixmap( 10,30,pix.width(),pix.height(),pix);
}
void MainWindow::connectDB()
{
    QString filename = "./coin.db";
    //判断是否有数据库
    QFileInfo info(filename);
    bool ret = info.exists();
    //创建或打开数据库
    db = QSqlDatabase::addDatabase("QSQLITE");
    //db.setHostName("127.0.0.1");
   // db.setUserName("root");
   // db.setPassword("123456");
    db.setDatabaseName(filename);

    if(db.open())
    {
        if(ret == false)             //创建表
        {
           QString cmd = "create table account(name text primary key,password text,grade int);";
           QSqlQuery query(db);
           query.exec(cmd);
        }
    }
}

void MainWindow::on_pushButtonlogin_clicked()
{
    if(ui->lineEdituser->text().isEmpty() || ui->lineEditpassword->text().isEmpty())
    {
         QMessageBox::warning(this,"error","add more infomation");
    }
    else
    {
         QSqlQuery temquery(db);
         QSqlQuery temquery2(db);
         bool tem = temquery.exec("select name , password from manager where name = '"+ ui->lineEdituser->text()

            +"'AND password = '"+ ui->lineEditpassword->text()+"';");
         if(tem)
         {
            user_grade = temquery.value(2).toInt();
         }
         else
         {
            QString cmd2 = "insert into account values('"+ ui->lineEdituser->text()

                    +"','"+ ui->lineEditpassword->text()+"',0);";
            temquery2.exec(cmd2);
            user_grade = 0;
         }  
    }
    //将自身隐藏，显示选择关卡场景
    this->hide();
    choosescene->show();
    //添加音效
    QSound *startSound = new QSound(":/TapButtonSound.wav",this);
    startSound->play(); //开始音效

}
void MainWindow::myslot(int a)
{
    qDebug()<<a;
    if(user_grade<a)          //用户原关卡记录比当前通关关卡低，更新数据库
    {
        user_grade=a;
        QSqlQuery temquery3(db);
        QString cmd3 = QString("update account set grade=%1 where name = '"+ ui->lineEdituser->text()

                +"'AND password = '"+ ui->lineEditpassword->text()+"';").arg(this->user_grade);
        temquery3.exec(cmd3);
    }
}
void MainWindow::sortslot()
{
    QSqlQueryModel *model=new QSqlQueryModel;
    QString cmd="select name,grade from account order by grade desc";
    model->setQuery(cmd,db);
    model->setHeaderData(0,Qt::Horizontal,tr("用户名"));
    model->setHeaderData(1,Qt::Horizontal,tr("最高关卡"));
    resultview.setModel(model);
    resultview.show();
}
void MainWindow::sortslot1()
{
    resultview.hide();
}
