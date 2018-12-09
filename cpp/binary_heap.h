//
//  binary_heap.h
//  cpp_solutions
//
//  Created by Сергей Петров on 07/11/2018.
//  Copyright © 2018 SergioPetrovx. All rights reserved.
//

#ifndef binary_heap_h
#define binary_heap_h

class Heap {
    static const int SIZE = 1000; // максимальный размер кучи
    std::pair<int, int> *elems;         // указатель на массив кучи
    int *vertex;
    int HeapSize; // размер кучи
public:
    Heap();  // конструктор кучи
    void addelem(int, int);  // добавление элемента кучи
    std::pair<int, int> getmax();
    void heapify(int);
    void updateelem(int, int);
};

void Heap::updateelem(int i, int data)
{
    i = vertex[i];
    elems[i].second = data;
}

Heap::Heap() {
    elems = new std::pair<int, int>[SIZE];
    vertex = new int[SIZE];
    HeapSize = 0;
}

void Heap::addelem(int index, int data) {
    int i, parent;
    i = HeapSize;
    elems[i].first = index;
    elems[i].second = data;
    vertex[index] = i;
    parent = (i-1)/2;
    while(parent >= 0 && i > 0)  {
        if(elems[i].second > elems[parent].second) {
            std::pair<int, int> temp = elems[i];
            elems[i] = elems[parent];
            elems[parent] = temp;
            
            int tmp2 = vertex[index];
            vertex[index] = vertex[parent];
            vertex[parent] = tmp2;
        }
        i = parent;
        parent = (i-1)/2;
    }
    HeapSize++;
}

void Heap::heapify(int i) {
    int left, right;
    std::pair<int, int> temp;
    left = 2*i+1;
    right = 2*i+2;
    if(left < HeapSize) {
        if(elems[i].second < elems[left].second) {
            temp = elems[i];
            elems[i] = elems[left];
            elems[left] = temp;
            
            int tmp2 = vertex[elems[i].first];
            vertex[elems[i].first] = vertex[elems[left].first];
            vertex[elems[left].first] = tmp2;
            heapify(left);
        }
    }
    if(right < HeapSize) {
        if(elems[i].second < elems[right].second) {
            temp = elems[i];
            elems[i] = elems[right];
            elems[right] = temp;
            
            int tmp2 = vertex[elems[i].first];
            vertex[elems[i].first] = vertex[elems[right].first];
            vertex[elems[right].first] = tmp2;
            heapify(right);
        }
    }
}

std::pair<int, int> Heap::getmax(void) {
    std::pair<int, int> x = elems[0];
    vertex[elems[HeapSize-1].first] = 0;
    elems[0] = elems[HeapSize-1];
    HeapSize--;
    heapify(0);
    return(x);
}
#endif /* binary_heap_h */
