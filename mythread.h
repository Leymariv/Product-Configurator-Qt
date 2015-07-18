#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QApplication>
#include <QThread>
#include <QProcess>
#include <qdebug.h>

class MyThread : public QThread
{
    Q_OBJECT

public:
    MyThread();
    ~MyThread();
public slots:
    void run();

signals:
    void complete();

private:
    void unzipXlsx();
    void cmdDos(QString command);
};

#endif // MYTHREAD_H
