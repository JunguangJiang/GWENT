#include "dialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    int id0=0;
    int id1=1;
    Dialog w0(id0);   w0.show();     w0.playGameWith(id1,0);

    //Dialog w1(id1);   w1.show();     w1.acceptGame(id0,0);

    return a.exec();
}
