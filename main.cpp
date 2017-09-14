#include "dialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    int id0=0;
    int id1=1;
    Dialog w0(id0);   w0.show();

    return a.exec();
}
