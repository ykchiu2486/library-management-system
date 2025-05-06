#pragma once
#include "Book.h"
#include <vector>
#include <stdexcept>
using namespace std;

class Heap {
private:
    static bool compare(Book* a, Book* b) {
        return a->getSimilarity() < b->getSimilarity(); 
    }

    vector<Book*> arr;

    void heapifyDown(int index) {
        int largest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int size = arr.size();

        if (left < size && compare(arr[largest], arr[left]))
            largest = left;

        if (right < size && compare(arr[largest], arr[right]))
            largest = right;

        if (largest != index) {
            swap(arr[largest], arr[index]);
            heapifyDown(largest);  
        }
    }

    void heapifyUp(int index) {
        if (index == 0) return;
        int parent = (index - 1) / 2;

        if (compare(arr[parent], arr[index])) {
            swap(arr[parent], arr[index]);
            heapifyUp(parent);  
        }
    }

public:
    void insert(Book* b) {
        arr.push_back(b);                     
        heapifyUp(arr.size() - 1);            
    }

    Book* pop() {
        if (arr.empty()) throw runtime_error("Heap is empty!");

        Book* top = arr[0];
        arr[0] = arr.back();  
        arr.pop_back();       
        if (!arr.empty())
            heapifyDown(0);   
        return top;
    }

    bool isEmpty() const {
        return arr.empty();
    }

    int size() const {
        return arr.size();
    }

    Book* top() const {
        if (arr.empty()) throw runtime_error("Heap is empty!");
        return arr[0];
    }
};
