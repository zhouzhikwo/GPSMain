﻿#include <QtWidgets>
//#if defined(_MSC_VER) && (_MSC_VER >= 1600)
//# pragma execution_character_set("utf-8")
//#endif
#include "mainwindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//#if QT_VERSION < QT_VERSION_CHECK(5,0,0)
//#if defined(_MSC_VER) && (_MSC_VER < 1600)
//    QTextCodec::setCodecForTr(QTextCodec::codecForName("GB18030-0"));
//#else
//    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
//#endif
//#endif
    MainWindow w;

    w.show();

    return a.exec();
}
