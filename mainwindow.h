#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QSound>
#include <QMainWindow>
#include<QFileInfo>
#include<QSqlQuery>
#include"chooselevelsecene.h"
#include"playscene.h"
#include<QTableView>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //重写PaintEvent事件
    void paintEvent(QPaintEvent *);
    //连接数据库
    void connectDB();
    //选择关卡场景
    chooselevelsecene *choosescene = NULL;
    //自定义槽函数接收
    void myslot(int);
    void sortslot();
    void sortslot1();
    QTableView resultview;
private slots:
    void on_pushButtonlogin_clicked();

private:
    Ui::MainWindow *ui;
    int user_grade;
    QSqlDatabase db;
};
#endif // MAINWINDOW_H
