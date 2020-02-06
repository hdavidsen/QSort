#ifndef SORTER_H
#define SORTER_H

#include "mainwindow.h"


class Sorter : public MainWindow {
     Q_OBJECT
public:
    Sorter(QWidget *parent = nullptr);
    ~Sorter();
    //void swap(double *a, double *b);

private:
    int counter, comparator, selector;
    double tmp;
    QVector<double> tmpData;
    bool initialized;

private slots:
    void resetButton() override;
    void selectionSort() override;
    void bubbleSort() override;
    void insertionSort() override;
    void heapSort() override;
    void mergeSort() override;
    // TODO: implement all of these (and more)
    // https://en.wikipedia.org/wiki/Sorting_algorithm
    // void quickSort() override;
    // void countingSort() override;
    // void radixSort() override;
    // void bucketSort() override;
    // void shellSort() override;


};

#endif // SORTER_H
