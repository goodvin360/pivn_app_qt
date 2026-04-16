#include <iostream>
#include  <locale.h>
#include <windows.h>
#include <QCoreApplication>
#include <QSerialPort>
#include "QSerialPortInfo"
#include <QDebug>
#include <QApplication>
#include <QMainWindow>
#include "ui_mainW.h"
#include "mainCaller.h"



int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    SetConsoleOutputCP(CP_UTF8);
    setlocale(LC_ALL, ".UTF8");
    mainWindow *window = new mainWindow(nullptr);

    Ui::MainWindow mainW;
    mainW.setupUi(window);

    foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())
        {mainW.comboBox->addItem(serialPortInfo.portName());}

    window->resize(480, 640);
    window->show();
    window->mWin = window;
    return QApplication::exec();
}



