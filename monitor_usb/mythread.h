#ifndef MYTHREAD_H
#define MYTHREAD_H

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

#include"mysdc.h"


class Mythread:public QThread
{
    Q_OBJECT

public:
    int receive=0;
    int supper=0;
    QString usbpath="/dev/sdb1";
    QString devpath="/media/liu/usb_1_device";

    QString usbpath_2="/dev/sdc1";
    QString devpath_2="/media/liu/usb_2_device";


    int check(){    //return 1 get  or not    
        FILE   *stream;
        int i=0;
        int j_mass_count=0;
        int x,a,b,c,d;//mass storage
        char   buf[10000];

        memset( buf, '\0', sizeof(buf) );     //初始化buf,以免后面写如乱码到文件中
        stream = popen( "lsusb -v", "r" );       //将“ls －l”命令的输出 通过管道读取（“r”参数）到FILE* stream
        fread( buf, sizeof(char), sizeof(buf), stream);      //将刚刚FILE* stream的数据流读取到buf中
        pclose( stream );


        for(i=0;i<strlen(buf);i++){
                if(buf[i]=='8'){
                    x=i+1;a=i+2;b=i+3;c=i+4;d=i+5;
                    if((buf[x]==' ')&&(buf[a]=='M')&&(buf[b]=='a')&&(buf[c]=='s')&&(buf[d]=='s')){
                        j_mass_count++;
                        qDebug()<<"find mass storage"<<j_mass_count;
                    }
                }
                //if(j==1)
                    //break;
        }

        if(j_mass_count==0)
            return 0;
        if(j_mass_count==1){
            if(supper==2){
               /* QProcess *pro_umount1=new QProcess;
                QString program_umount1="umount";

                QStringList arguments_umount1;
                arguments_umount1<<usbpath;
                pro_umount1->start(program_umount1,arguments_umount1);
                qDebug()<<"umount /dev/sdb1  =";

               QTime t1;
               t1.start();
               while(t1.elapsed()<30)
                    QCoreApplication::processEvents();

               QProcess *pro_umount2=new QProcess;
               QString program_umount2="umount";

               QStringList arguments_umount2;
               arguments_umount2<<usbpath_2;
               pro_umount2->start(program_umount2,arguments_umount2);
               qDebug()<<"umount /dev/sdc1  =";

               QTime t2;
               t2.start();
               while(t2.elapsed()<30)
                    QCoreApplication::processEvents();*/

               supper=0;
               return 0;

            }
            return match_device(buf);
        }
        if(j_mass_count==2){
            supper=2;
            return match_device(buf);
        }


    }
    //0  no match
    //1  match 1 device
    //2  mtach 2 device


    int match_device(char *buf){
        char usb_idv[10]="0x0ed1";
        char usb_idp[10]="0x6981";

        char usb_idv_2[10]="0x058f";
        char usb_idp_2[10]="0x6366";

        int p,q,r,s,t,u;
        int v,w,z,h,k,m,n;
        int inner=0;

        int real=0;

        for(inner=0;inner<strlen(buf);inner++){
            if(buf[inner]==usb_idv[0]){
                p=inner+1;q=inner+2;r=inner+3;s=inner+4;t=inner+5;
                if((buf[p]==usb_idv[1])&&(buf[q]==usb_idv[2])&&(buf[r]==usb_idv[3])&&(buf[s]==usb_idv[4])&&(buf[t]==usb_idv[5])){
                    u=t;
                    qDebug()<<"find idVendor: 0x0ed1";
                    while(u<t+100){
                        if(buf[u]==usb_idp[0]){
                            v=u+1;w=u+2;z=u+3;h=u+4;k=u+5;
                            if((buf[v]==usb_idp[1])&&(buf[w]==usb_idp[2])&&(buf[z]==usb_idp[3])&&(buf[h]==usb_idp[4])&&(buf[k]==usb_idp[5])){
                                real++;
                                qDebug()<<"find idProduct 0x6981\n";
                                break;
                            }
                        }
                        u++;
                    }//while
                }
            }
            if(buf[inner]==usb_idv_2[0]){
                p=inner+1;q=inner+2;r=inner+3;s=inner+4;t=inner+5;
                if((buf[p]==usb_idv_2[1])&&(buf[q]==usb_idv_2[2])&&(buf[r]==usb_idv_2[3])&&(buf[s]==usb_idv_2[4])&&(buf[t]==usb_idv_2[5])){
                    u=t;
                    qDebug()<<"find idVendor: 0x058f";
                    while(u<t+100){
                        if(buf[u]==usb_idp_2[0]){
                            v=u+1;w=u+2;z=u+3;h=u+4;k=u+5;
                            if((buf[v]==usb_idp_2[1])&&(buf[w]==usb_idp_2[2])&&(buf[z]==usb_idp_2[3])&&(buf[h]==usb_idp_2[4])&&(buf[k]==usb_idp_2[5])){
                                real++;
                                qDebug()<<"find idProduct 0x6366\n";
                                break;
                            }
                        }
                        u++;
                    }//while
                }
            }
        }//for

        return real;
    }
    //0 no;  1  1device;    2   2device;

    int flag=0;
    Mysdc mysdc;

    void dis(){
        mysdc.start();

        while(1){
            receive=check();
            if(receive == 1){
                flag=1;
                //mkdir
                QProcess *pro_mk=new QProcess;
                QString program_mk="mkdir";
                QStringList arguments_mk;
                arguments_mk<<devpath;
                pro_mk->start(program_mk,arguments_mk);

                QTime t1;
                t1.start();
                while(t1.elapsed()<400)
                        QCoreApplication::processEvents();

                //mount
                    QProcess *pro=new QProcess;
                    QString program="mount";

                    QStringList arguments;
                    arguments<<"-o";
                    arguments<<"ro,iocharset=utf8";                                  //源文件路径
                    arguments<<usbpath;
                    arguments<<devpath;

                    pro->start(program,arguments);

                    QTime t2;
                    t2.start();
                    while(t2.elapsed()<3600)
                            QCoreApplication::processEvents();
             }
           else if(receive == 2){
                flag=2;
                //mkdir
               QProcess *pro_mk=new QProcess;
               QString program_mk="mkdir";
               QStringList arguments_mk;
               arguments_mk<<devpath_2;
               pro_mk->start(program_mk,arguments_mk);

               QTime t1;
               t1.start();
               while(t1.elapsed()<400)
                       QCoreApplication::processEvents();

               //mount
               QProcess *pro=new QProcess;
               QString program="mount";

               QStringList arguments;
               arguments<<"-o";
               arguments<<"ro,iocharset=utf8";                                  //源文件路径
               arguments<<usbpath_2;
               arguments<<devpath_2;

               pro->start(program,arguments);

               QTime t2;
               t2.start();
               while(t2.elapsed()<3600)
                       QCoreApplication::processEvents();
           }

            else {
                flag=0;
               QProcess *pro_umount2=new QProcess;
               QString program_umount2="umount";

               QStringList arguments_umount2;
               arguments_umount2<<usbpath;
               pro_umount2->start(program_umount2,arguments_umount2);
               qDebug()<<"umount /dev/sdb1  =";

               QTime t1;
               t1.start();
               while(t1.elapsed()<30)
                    QCoreApplication::processEvents();

               QProcess *pro_rm=new QProcess;
               QString program_rm="rm";
               QStringList arguments_rm;
               arguments_rm<<"-rf";
               arguments_rm<<devpath;
               pro_rm->start(program_rm,arguments_rm);
               qDebug()<<"rm -rf";

               QTime t2;
               t2.start();
               while(t2.elapsed()<30)
                    QCoreApplication::processEvents();

               //////////////////////////////////////////////////////////////////////


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


              QProcess *pro_rm3=new QProcess;
              QString program_rm3="rm";
              QStringList arguments_rm3;
              arguments_rm3<<"-rf";
              arguments_rm3<<devpath_2;
              pro_rm3->start(program_rm3,arguments_rm3);
              qDebug()<<"rm -rf";

              QTime t4;
              t4.start();
              while(t4.elapsed()<30)
                   QCoreApplication::processEvents();

            }
           //////////////////////////////////////////////////////////////
           //// thread2 umount sdc2
        /*    if(flag==1){
                if(!mysdc.isRunning()){ //panduan shifou qidong
                    mysdc.start();//start thread2
                }
            }
            else{
                if(mysdc.isRunning()){
                    mysdc.terminate();//stop thread2
                    QTime t4;
                    t4.start();
                    while(t4.elapsed()<100)
                         QCoreApplication::processEvents();
                }

            }*/
          //////////////////////////////////////
            if(flag==1){
                mysdc.mark_true();
            }
            else{
                mysdc.mark_false();
            }

        }
    }

protected:
    void run(){
        dis();
    }
};





#endif // MYTHREAD_H
