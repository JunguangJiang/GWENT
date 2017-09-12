#include "dialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w0(0);w0.show();

    //Dialog w1(1);w1.show();


    return a.exec();
}
