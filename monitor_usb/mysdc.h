#ifndef MYSDC_H
#define MYSDC_H


#include<qthread.h>
#include"mainwindow.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include<QDebug>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>



class Mysdc:public QThread
{
    Q_OBJECT

public:

    QString usbpath_2="/dev/sdc1";
    QString devpath_2="/media/liu/usb_2_device";
    int mark=0;

    void dis(){

        while(1){
            while(mark==1){
                QProcess *pro_umount3=new QProcess;
                QString program_umount3="umount";

                QStringList arguments_umount3;
                arguments_umount3<<usbpath_2;
                pro_umount3->start(program_umount3,arguments_umount3);
                qDebug()<<"umount /dev/sdc1  =";


                QTime t3;
                t3.start();
                while(t3.elapsed()<30)
                    QCoreApplication::processEvents();
            }
            QTime t2;
            t2.start();
            while(t2.elapsed()<1000)
                QCoreApplication::processEvents();
        }
    }


    void mark_true(){
        mark=1;
    }
    void mark_false(){
        mark=0;
    }

protected:
    void run(){
        dis();
    }
};






#endif // MYSDC_H
