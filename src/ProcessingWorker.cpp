#include "ProcessingWorker.h"
#include "cmath"

ProcessingWorker::ProcessingWorker() {
    number.clear();
    portData.clear();
}

ProcessingWorker::~ProcessingWorker() {

}

void ProcessingWorker::process(QByteArray data) {
    static QByteArray buffer;
    buffer += data;
    portDataPart = data;

    std::cout << data.toStdString() << std::endl;


    QVector<double> result;

    int min = 1, max = 100;
    // Formula: min + (rand() % (max - min + 1))
    int random_num = min + (std::rand() % (max - min + 1));
//    result.push_back(random_num);

    /*while (true) {
        int start = buffer.indexOf('<');
        int end   = buffer.indexOf('>');

        if (start == -1 || end == -1 || end < start)
        break;

        QByteArray packet = buffer.mid(start + 1, end - start - 1);
        buffer.remove(0, end + 1);

        QList<QByteArray> parts = packet.split(':');

        for (auto &p : parts)
            result.append(p.toDouble());
    }*/

    num++;
    number.push_back(num);
    portData.push_back(data.toStdString());

    double sinData = std::sin(num*3.14/180);
    result.push_back(sinData);

    if (!result.isEmpty())
            emit processedData(result);

}

void ProcessingWorker::fileWrite() {
    std::fstream fout("../results.txt", std::ios::out);
    for (int i=0; i<number.size()-1; i++)
        fout << number.at(i) << '\t' << portData.at(i) << '\n';
    fout.close();
    num = 0;
    number.clear();
    portData.clear();
}
