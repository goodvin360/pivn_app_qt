#include "Plotter.h"
#include "iostream"

Plotter::Plotter() {
    chart = new Chart();
    chartView = new ChartView(chart);

    m_axisX = new QValueAxis();
    m_axisY = new QValueAxis();
    series = new QLineSeries();
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

void Plotter::plotGraph() {

    int min = 1, max = 100;
    // Formula: min + (rand() % (max - min + 1))
    int random_num = min + (std::rand() % (max - min + 1));
    vecData.push_back(random_num);
    std::cout << random_num << std::endl;

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


