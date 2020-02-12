#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore/QTimer>
#include  "qcustomplot.h"

#include <QDebug>
#include <iostream>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
     MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
     void setSorter(int idx);
     void updateGUI();
     // TODO: figure out how/if these can be private again
     QTimer *m_timer;
     QVector<double> keyData, valueData, resetData;
     int arraySize;

private slots:
    void startButton();
    virtual void resetButton() = 0;
    virtual void selectionSort() = 0;
    virtual void quickSort() = 0;
    virtual void bubbleSort() = 0;
    virtual void insertionSort() = 0;
    virtual void heapSort() = 0;
    virtual void mergeSort() = 0;
    virtual void countingSort() = 0;
    virtual void radixSort() = 0;
    // TODO: implement all of these (and more)
    // https://en.wikipedia.org/wiki/Sorting_algorithm
    // virtual void bucketSort() = 0;
    // virtual void shellSort() = 0;

private:
    Ui::MainWindow *ui;
    QCustomPlot *customPlot;
    QCPBars *myBars;
    QCPTextElement *title;
    bool isMoved;
};

#endif // MAINWINDOW_H
