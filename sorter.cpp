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
    selector = counter;

    // Inner sorting loop
    for(comparator = counter+1; comparator < arraySize; comparator++){
        if(valueData[comparator] < valueData[selector])  {
            selector = comparator;
        }
    }

    // TODO: figure out why better swap method (supposedly in 5.14) isn't working --
    // --> valueData.swapItemsAt(counter, min);
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
        // keep this one
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
    comparator = selector + 1;

    if (valueData[selector] > valueData[comparator]) {
        swap1 = valueData[comparator];
        swap2 = valueData[selector];
        //Swap(&swap1, &swap2);
        valueData.replace(selector, swap1);
        valueData.replace(comparator, swap2);
    }
    updateGUI();

    // Checks if the sorting algorithm has passed through the inner loop, then the entire array
    if(selector < arraySize-counter-2){
        // Debugging
        // TODO: Remove when everything works
        std::cout << "selector = " << selector << " | ";
        selector++;
    }else {
        selector=0;
        counter++;
        // Debugging
        // TODO: Remove when everything works
        std::cout << "\n";
        for(int k=0; k<arraySize; k++) {
            std::cout << valueData[k] << "  " << std::flush;
        }
        std::cout << "\n";
        if(counter == arraySize-1) {
            // Debugging
            // TODO: Replace with/add GUI message when everything works
            std::cout << "Doneso!\nCounter = " << counter << " | comparator = " << comparator << " | selector = " << selector << std::endl;
            std::cout << "Final Result:" << std::endl;
            for(int k=0; k<arraySize; k++){
                std::cout << valueData[k] << " -> " << std::flush;
            }
            std::cout << ":D" << std::endl;
            // keep this one
            m_timer->stop();
        }
    }
}

void Sorter::insertionSort() {
    if(counter == 0 ) counter++;

    // TODO: fix! implicit typecast
    selector = valueData[counter];
    comparator = counter - 1;

    while (comparator >= 0 && valueData[comparator] > selector) {
        valueData[comparator + 1] = valueData[comparator];
        comparator--;
    }

    valueData[comparator + 1] = selector;
    updateGUI();


    if(counter == arraySize-1) {
        // Debugging
        // TODO: Replace with/add GUI message when everything works
        std::cout << "Doneso!\nCounter = " << counter << " | comparator = " << comparator << " | selector = " << selector << std::endl;
        std::cout << "Final Result:" << std::endl;
        for(int k=0; k<arraySize; k++){
            std::cout << valueData[k] << " -> " << std::flush;
        }
        std::cout << ":D" << std::endl;
        // keep this one
        m_timer->stop();
    }else{
        counter++;
        // Debugging
        // TODO: Remove when everything works
        for(int k=0; k<arraySize; k++) {
            std::cout << valueData[k] << "  " << std::flush;
        }
        std::cout << "\n";
    }
}

void Sorter::heapSort() {
    // Building the max heap
    // TODO: figure out how/if this should be displayed
    // TODO: fix naming conventions
    if(counter == 0 && selector == 0 && comparator == 0) {
        std::cout << "Max heaping..\n";
        for (int i = 1; i < arraySize; i++) {
            // if child is bigger than parent
            if (valueData[i] > valueData[(i - 1) / 2]) {
                int z = i;

                // swap child and parent until
                // parent is smaller
                while (valueData[z] > valueData[(z - 1) / 2]) {
                    swap1 = valueData[z];
                    swap2 = valueData[(z-1)/2];
                    //Swap(&swap1, &swap2);
                    valueData.replace((z-1)/2, swap1);
                    valueData.replace(z, swap2);
                    z = (z - 1) / 2;
                }
            }
        }

        counter = arraySize - 1;

        std::cout << "Max heaped..\n";
        // Debugging
        // TODO: Remove when everything works
        for(int k=0; k<arraySize; k++) {
            std::cout << valueData[k] << "  " << std::flush;
        }
        std::cout << "\n";
    }
    // swap value of first indexed with last indexed
    swap1 = valueData[0];
    swap2 = valueData[counter];
    //Swap(&swap1, &swap2);
    valueData.replace(counter, swap1);
    valueData.replace(0, swap2);

    updateGUI();

    // maintaining heap property after each swapping
    comparator = 0, selector = 1;

    // TODO: take out of loop, to be displayed
    while (selector < counter) {
        // if left child is smaller than right child point index variable to right child
        if (valueData[selector] < valueData[selector + 1] && selector < (counter - 1))
            selector++;

        // if parent is smaller than child then swapping parent with child having higher value
        if (valueData[comparator] < valueData[selector] && selector < counter) {
            swap1 = valueData[comparator];
            swap2 = valueData[selector];
            //Swap(&swap1, &swap2);
            valueData.replace(selector, swap1);
            valueData.replace(comparator, swap2);
        }

        comparator = selector;
        selector = (2 * comparator + 1);

    }

    if(counter == 0) {
        // Debugging
        // TODO: Replace with/add GUI message when everything works
        std::cout << "Doneso!\nCounter = " << counter << " | comparator = " << comparator << " | selector = " << selector << std::endl;
        std::cout << "Final Result:" << std::endl;
        for(int k=0; k<arraySize; k++){
            std::cout << valueData[k] << " -> " << std::flush;
        }
        std::cout << ":D" << std::endl;
        // keep this one
        m_timer->stop();
    }else{
        counter--;
        // Debugging
        // TODO: Remove when everything works
        for(int k=0; k<arraySize; k++) {
            std::cout << valueData[k] << "  " << std::flush;
        }
        std::cout << "\n";
    }
}


// TODO(ish): not necessary (for now?)
/*
void Sorter::Swap(double *a, double *b) {
    double temp = *a;
    *a = *b;
    *b = temp;
}
*/
