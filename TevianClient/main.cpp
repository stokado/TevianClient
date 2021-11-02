#include "tevianclient.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    TevianClient w;
    w.show();
    return app.exec();
}
