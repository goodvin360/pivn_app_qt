#include "Plotter.h"
#include "iostream"

Plotter::Plotter() {

    timer = new QTimer(this);

    connect(timer, &QTimer::timeout, this, &Plotter::plotGraph);

    timer->start(1);


    chart = new Chart();
    chartView = new ChartView(chart);

    m_axisX = new QValueAxis();
    m_axisY = new QValueAxis();
    series = new QLineSeries();
    series->setUseOpenGL(true);
    chart->addSeries(series);
    chart->legend()->setVisible(true);
    chart->setVisible(true);
    chart->addAxis(m_axisX, Qt::AlignBottom);
    chart->addAxis(m_axisY, Qt::AlignLeft);
    series->attachAxis(m_axisX);
    series->attachAxis(m_axisY);
    m_axisX->setTickCount(10);
    m_axisY->setTickCount(10);
    m_axisX->setRange(0,200);
    m_axisY->setRange(0,100);
    m_axisX->setMinorTickCount(5);
    m_axisY->setMinorTickCount(5);
    m_axisX->applyNiceNumbers();
    m_axisY->applyNiceNumbers();
    chartView->setGeometry(500,500,500,500);

}

Plotter::~Plotter() {
    delete chart;
    delete chartView;

}

void Plotter::onParsedData(QVector<double> values) {
    QMutexLocker locker(&mutex);
    buffer += values;
}

/*void Plotter::flushToPlot() {
    QVector<double> local;
    {
        QMutexLocker locker(&mutex);
        local.swap(buffer);
    }
    if (local.isEmpty())
        return;

    static double x = 0;

    for (double v :local) {
        mySeries->append(x++, v);
    }

    if (mySeries->count()>2000) {
        mySeries->removePoints(0, mySeries->count()-2000);
    }
}*/

void Plotter::plotGraph() {

    QVector<double> local;
    {
        QMutexLocker locker(&mutex);
        local.swap(buffer);
    }
    if (local.isEmpty())
        return;

    static double x = 0;

    for (double v :local) {
        vecData.push_back(v);
        if (vecData.size()>rescaleSize)
        {
            vecData.erase(vecData.begin(), vecData.end()-rescaleSize);
        }
    }

    QVector<QPointF> points(2 * vecData.size());
    for (std::vector<int>::size_type l = 0; l != vecData.size(); ++l) {
//                points[l] = QPointF(l, vecData.at(2+i)[l]);
        for (int m = 0; m <= l; m++) {
            if (l == m) {
                points[l + m] = QPointF(l+vecData.front(), vecData[l]);
                points[l + m + 1] = QPointF(l + 1+vecData.front(), vecData[l]);
            }
        }
    }
    QPen pen = series->pen();
    pen.setWidth(1);
    series->setPen(pen);
    series->replace(points);

    maxValVec.clear();
    maxValVec.push_back(*max_element(vecData.begin(), vecData.end()));
    max_y = *max_element(maxValVec.begin(), maxValVec.end());
    m_axisX->setRange(0, vecData.size());
    m_axisY->setRange(0, 1.2 * max_y);
    if (max_y == 0)
        m_axisY->setRange(0, 1);

    chartView->setVisible(true);
    chartView->isOn = true;
}


