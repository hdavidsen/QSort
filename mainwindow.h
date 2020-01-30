#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore/QTimer>
#include  "qcustomplot.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
     MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
     //void Swap(double *a, double *b);
     void setSorter(int idx);
     void updateGUI();

     // TODO: figure out how to make this private again
     QTimer *m_timer;
     QVector<double> keyData, valueData, resetData;
     int arraySize;


private slots:
    void startButton();
    virtual void resetButton() = 0;
    virtual void selectionSort() = 0;
    virtual void bubbleSort() = 0;

private:
    Ui::MainWindow *ui;
    QCustomPlot *customPlot;
    QCPBars *myBars;
    QCPTextElement *title;
    bool isMoved;
};

#endif // MAINWINDOW_H
