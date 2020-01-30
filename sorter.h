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
    double swap1, swap2;

private slots:
    void resetButton() override;
    void selectionSort() override;
    void bubbleSort() override;


};

#endif // SORTER_H
