#include <QApplication>
#include <windows.h>
#include <test.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Windows mainWindow;
    mainWindow.show();

//   FenPrinc fen;
//    fen.show();

    return app.exec();
}
