#include "widget.h"
#include <QApplication>
#include <QSplashScreen>
#include "mainwindow.h"
//qt5.5 MinGW 32bit
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString strLibPath(QDir::toNativeSeparators(QApplication::applicationDirPath())+QDir::separator()+
    "sqldrivers");
    a.addLibraryPath(strLibPath);
//    QTextCodec::setCodecForTr(QTextCodec::codecForName("GBK"));
    QSplashScreen *pSplash = new QSplashScreen;
    pSplash->setPixmap(QPixmap(":/images/images/splash.jpg"));
    pSplash->show();
    Qt::Alignment center = Qt::AlignCenter;
    pSplash->showMessage(QString::fromWCharArray(L"正在努力加载数据中，请稍后……"),center,Qt::blue);

    MainWindow w1;
    w1.show();

//    Widget w;
//    w.showMaximized();
    pSplash->finish(&w1);
    delete pSplash;
    return a.exec();
}
