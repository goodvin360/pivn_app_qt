#include "mainCaller.h"

mainWindow::mainWindow(QWidget *parent) : QMainWindow(parent) {

    parent = nullptr;

    this->setAttribute(Qt::WA_DeleteOnClose);

    m_timer = new QTimer();
    connect(m_timer, &QTimer::timeout, this, &mainWindow::startByTimer);
    m_timer->setInterval(1000);

}

mainWindow::~mainWindow() {

}

void mainWindow::startByTimer() {

}

void mainWindow::addStart() {
    serialThread = new QThread(this);

    worker = new SerialWorker(nullptr, portName);

    worker->moveToThread(serialThread);

    connect(serialThread, &QThread::started, worker, &SerialWorker::startWork);
    connect(worker, &SerialWorker::dataReceived, this, &mainWindow::handleData);
    connect(worker, &SerialWorker::error, this, [](QString err){qDebug() << "Serial error:" << err;});
    connect(this, &QObject::destroyed, worker, &SerialWorker::stopWork);
    connect(serialThread, &QThread::finished, worker, &QObject::deleteLater);

    serialThread->start();
    myPlotter = new Plotter();



//    number.clear();
//    portData.clear();

//    std::cout << myData.toStdString() << std::endl;

//    m_timer->start();
}

void mainWindow::addStop() {
//    m_timer->stop();
    serialThread->quit();
    serialThread->wait();

    /*std::fstream fout("../results.txt", std::ios::out);
    for (int i=0; i<number.size()-1; i++)
        fout << number.at(i) << '\t' << portData.at(i) << '\n';
    fout.close();
    num = 0;*/
}

void mainWindow::handleData(QByteArray data) {
//    qDebug() << "GUI thread:" << QThread::currentThread();
    myData = data;
//    std::cout << data.toStdString() << std::endl;
    myPlotter->plotGraph();

    /*num++;
    number.push_back(num);
    portData.push_back(data.toStdString());*/

}


void mainWindow::getCOM(QString itemName) {
    std::string tempStr = itemName.toStdString();
    for (int i=0; i<tempStr.size(); i++) {
        if (tempStr[i]<'0'|| tempStr[i]>'9')
            tempStr.erase(0, tempStr.find(tempStr[i])+1);
    }

    int portNum = std::stoi(tempStr);

    std::stringstream portString;
    if (portNum>1 && portNum<=9) {
        portString << "COM" << portNum;
    }
    else if (portNum>9) {
        portString << "\\\\.\\COM" << portNum;
    }

    portName = portString.str();
}
