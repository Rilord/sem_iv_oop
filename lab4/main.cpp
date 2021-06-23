//
// Created by Kirill Diordiev on 26.05.2021.
//

#include <ui/mainwindow.h>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window;
    window.show();

    return app.exec();
}