#include "mainwindow.h"
#include <QApplication>

/*
 * Language:
 * language-Chooser example, https://wiki.qt.io/How_to_create_a_multi_language_application
 */

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    try {
        QStringList cmdline_args = QCoreApplication::arguments();

        for(int i=0;i<cmdline_args.count();i++)
        {
            QString fileName = cmdline_args.at(i);
            if(fileName.toLower().contains(".xyz") || fileName.toLower().contains(".txt") ){
                //open File
                w.open_File(fileName);
                break;
            }
        }
    } catch (exception e) {
        qDebug()<< e.what();
    }

    return a.exec();
}
