#ifndef SELECTIONSORT_H
#define SELECTIONSORT_H

template <typename T, typename Compare = std::less<T>>
void SelectionSort(T arr[], int size, Compare comp = Compare()) {
    for (int i = 0; i < size - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < size; ++j) {
            if (comp(arr[j], arr[minIndex])) {
                minIndex = j;
            }
        }
        std::swap(arr[i], arr[minIndex]);
    }
}

#endif
