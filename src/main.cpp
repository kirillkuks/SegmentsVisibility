#include "segment_Vis.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Segment_Vis w;
    w.show();
    return a.exec();
}
