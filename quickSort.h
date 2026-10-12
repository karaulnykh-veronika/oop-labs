#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <vector>
using namespace std;

template <class T> // разбиение - элементы меньше pivot влево
int partition(vector<T>& arr, int low, int high) {
    T pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

template <class T> // рекурсивная быстрая сортировка
void quickSort(vector<T>& arr, int low, int high) {
    if (low < high) {
        int p = partition(arr, low, high);
        quickSort(arr, low, p - 1);
        quickSort(arr, p + 1, high);
    }
}

#endif