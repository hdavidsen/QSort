#include "sorter.h"
#include <iostream>

Sorter::Sorter(QWidget *parent) : MainWindow(parent) {
    counter = 0;
    comparator = 0;
    selector = 0;
}

Sorter::~Sorter() {

}

void Sorter::resetButton() {
    counter = 0;
    comparator = 0;
    selector = 0;
    valueData = resetData;
    updateGUI();
}

void Sorter::selectionSort() {
    // Inner sorting loop
    selector = counter;
    for(comparator = counter+1; comparator < arraySize; comparator++){
        if(valueData[comparator] < valueData[selector])  {
            selector = comparator;
        }
    }

    // TODO: figure out why better swap method (supposedly in 5.14) isn't working
    //valueData.swapItemsAt(counter, min);
    // TODO: use better Qvector<> swap method
    swap1 = valueData[selector];
    swap2 = valueData[counter];
    //Swap(&swap1, &swap2);
    valueData.replace(counter, swap1);
    valueData.replace(selector, swap2);

    // Update GUI
    updateGUI();

    // Checks if the sorting algorithm has passed through the entire array
    if(counter == arraySize-2) {
        // Debugging
        // TODO: Replace with/add GUI message when everything works
        std::cout << "Doneso!\nCounter = " << counter << " | min = " << selector << " | j = " << comparator << std::endl;
        std::cout << "Final Result:" << std::endl;
        for(int k=0; k<arraySize; k++){
            std::cout << valueData[k] << " -> " << std::flush;
        }
        std::cout << ":D" << std::endl;
        // not this one
        m_timer->stop();
    }else {
        counter++;
        // Debugging
        // TODO: Remove when everything works
        for(int k=0; k<arraySize; k++) {
            std::cout << valueData[k] << "  " << std::flush;
        }
        std::cout << "\n";
    }
}

void Sorter::bubbleSort() {
    comparator = counter;

    if (valueData[selector] > valueData[selector+1]) {
        swap1 = valueData[selector+1];
        swap2 = valueData[selector];
        //Swap(&swap1, &swap2);
        valueData.replace(selector, swap1);
        valueData.replace(selector+1, swap2);
    }
    updateGUI();

    // Checks if the sorting algorithm has passed through the entire array
    if(selector < arraySize-comparator-2){
        std::cout << "selector = " << selector << " | ";
        selector++;
    }else if(selector == arraySize-comparator-2) {
        selector=0;
        counter++;
        // Debugging
        // TODO: Remove when everything works
        std::cout << "\n";
        for(int k=0; k<arraySize; k++) {
            std::cout << valueData[k] << "  " << std::flush;
        }
        std::cout << "\n";
        if(counter == arraySize-2) {
            // Debugging
            // TODO: Replace with/add GUI message when everything works
            std::cout << "Doneso!\nCounter = " << counter << " | comparator = " << comparator << " | selector = " << selector << std::endl;
            std::cout << "Final Result:" << std::endl;
            for(int k=0; k<arraySize; k++){
                std::cout << valueData[k] << " -> " << std::flush;
            }
            std::cout << ":D" << std::endl;
            // not this one
            m_timer->stop();
        }
    }
}


// TODO(ish): not necessary (for now?)
/*
void MainWindow::Swap(double *a, double *b) {
    double temp = *a;
    *a = *b;
    *b = temp;
}
*/
