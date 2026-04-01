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
    std::cout << myData.toStdString() << std::endl;
}

void mainWindow::addStart() {
    portName = "COM8";
    serialThread = new QThread(this);

    worker = new SerialWorker(nullptr, portName);

    worker->moveToThread(serialThread);

    connect(serialThread, &QThread::started, worker, &SerialWorker::startWork);
    connect(worker, &SerialWorker::dataReceived, this, &mainWindow::handleData);
    connect(worker, &SerialWorker::error, this, [](QString err){qDebug() << "Serial error:" << err;});
    connect(this, &QObject::destroyed, worker, &SerialWorker::stopWork);
    connect(serialThread, &QThread::finished, worker, &QObject::deleteLater);

    serialThread->start();

    m_timer->start();
}

void mainWindow::addStop() {
    m_timer->stop();
    serialThread->quit();
    serialThread->wait();
}

void mainWindow::handleData(QByteArray data) {
//    qDebug() << "GUI thread:" << QThread::currentThread();
    myData = data;
//    std::cout << data.toStdString() << std::endl;
}
