#ifndef PIVN_APP_QT_SERIAL_MAINCALLER_H
#define PIVN_APP_QT_SERIAL_MAINCALLER_H

#include <iostream>
#include <tchar.h>
#include "QMainWindow"
#include "QtWidgets/QLineEdit"
#include "QtWidgets/QTextBrowser"
#include "QtWidgets/QComboBox"
#include "QtWidgets/QPushButton"
#include <QtSerialPort/QSerialPortInfo>
#include <QtSerialPort/QSerialPort>
#include "QFileDialog"
#include "QApplication"
#include "QScrollBar"
#include "windows.h"
#include <sstream>
#include "fstream"
#include "iomanip"
#include "thread"
#include "string"
#include "map"
#include "vector"
#include "math.h"
#include <QTextCodec>
#include <QTextStream>
#include "QTimer"
#include "QThread"
#include "serialWorker.h"
#include "fstream"
#include "Plotter.h"

#pragma region Docs

class mainWindow : public QMainWindow {
Q_OBJECT

public:
    mainWindow(QWidget* parent = nullptr);

    ~mainWindow();

    QMainWindow*mWin = new QMainWindow();

    QPushButton*pushButton = new QPushButton();
    QComboBox*comboBox = new QComboBox();


    std::string portName;
    QTimer*m_timer;
    Plotter*myPlotter;

private:
    QThread*serialThread;
    SerialWorker*worker;
    QByteArray myData;
    std::vector <int> number;
    std::vector <std::string> portData;

public slots:
    void addStart();
    void addStop();
    void startByTimer();
    void getCOM(QString itemName);
//    void connectCOM();

private slots:
    void handleData(QByteArray data);
};


#endif //PIVN_APP_QT_SERIAL_MAINCALLER_H
