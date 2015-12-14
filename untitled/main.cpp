#include <QtGui/QApplication>
#include "mainwindow.h"
#include <QTextCodec>
#include <QWSServer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QWSServer::setCursorVisible(false);
    //QTextCodec *CodeForPC = QTextCodec::codecForName("System");
    //QTextCodec *codeFor2440 = QTextCodec::codecForName("GB2312");
    QTextCodec *codeFor6410 = QTextCodec::codecForName("utf8");

    QTextCodec::setCodecForLocale(codeFor6410);
    QTextCodec::setCodecForCStrings(codeFor6410);
    QTextCodec::setCodecForTr(codeFor6410);
    MainWindow w;
    w.showFullScreen();
    return a.exec();
}

