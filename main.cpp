#include "mainwindow.h"
#include"dataconfig.h"
#include <QApplication>
#include<QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
 //   dataConfig config;
 //   for(int i=0;i<4;i++)
 //  {
 //     for(int j=0;j<4;j++)
 //      {
 //         qDebug()<<config.mData[1][i][j]<<" ";
 //      }
 //   }
    return a.exec();
}
