#include <iostream>

void SiftUp(int index, int *arr, bool max = false) {
    while (index > 0 && (!max && arr[index] < arr[(index - 1) / 2] || max && arr[index] > arr[(index - 1) / 2])) {
        std::swap(arr[index], arr[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

void SiftDown(int index, int size, int *arr, bool max = false) {
    int i, l, r;
    while (index < size) {
        i = index;
        l = index * 2 + 1;
        r = l + 1;
        if (l < size && (!max && arr[i] > arr[l] || max && arr[i] < arr[l])) {
            i = l;
        }
        if (r < size && (!max && arr[i] > arr[r] || max && arr[i] < arr[r])) {
            i = r;
        }
        if (i == index) break;
        std::swap(arr[index], arr[i]);
        index = i;
    }
}

void Insert(int element, int index, int *arr, bool max = false) {
    arr[index] = element;
    SiftUp(index, arr, max);
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int n;
    std::cin >> n;
    int max_heap[n / 2 + 1];
    int min_heap[n / 2];
    int max_heap_size = 0;
    int min_heap_size = 0;
    int value;
    for (int i = 0; i < n; i++) {
        std::cin >> value;
        if (max_heap_size <= min_heap_size) {
            if (min_heap_size && value > min_heap[0]) {
                Insert(min_heap[0], max_heap_size++, max_heap, true);
                min_heap[0] = value;
                SiftDown(0, min_heap_size, min_heap);
            } else {
                Insert(value, max_heap_size++, max_heap, true);
            }
        } else {
            if (max_heap_size && value < max_heap[0]) {
                Insert(max_heap[0], min_heap_size++, min_heap);
                max_heap[0] = value;
                SiftDown(0, max_heap_size, max_heap, true);
            } else {
                Insert(value, min_heap_size++, min_heap);
            }
        }
        std::cout << (max_heap_size == min_heap_size ? (max_heap[0] + min_heap[0]) / 2 : max_heap[0]) << '\n';

    }
}
