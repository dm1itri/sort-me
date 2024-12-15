#include <iostream>

void SiftUp(int index, int *arr) {
    while (index > 0 && arr[index] < arr[(index - 1) / 2]) {
        std::swap(arr[index], arr[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

void SiftDown(int index, int size, int *arr) {
    int i, l, r;
    while (index < size) {
        i = index;
        l = index * 2 + 1;
        r = l + 1;
        if (l < size && arr[i] > arr[l]) {
            i = l;
        }
        if (r < size && arr[i] > arr[r]) {
            i = r;
        }
        if (i == index) break;
        std::swap(arr[index], arr[i]);
        index = i;
    }
}

int main() {
    int a = 0;
    for (int i = 0; i < 1000000000; i ++) {
        a ++;
    }
    std::cout << a << std::endl;
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int n;
    std::cin >> n;
    int min_heap[n];
    int min_heap_size = n;
    for (int &i : min_heap) std::cin >> i;
    for (int i = n / 2; i >= 0; i--) {
        SiftUp(i, min_heap);
        SiftDown(i, min_heap_size, min_heap);
    }
    for (int i = 0; i < n; i++) {
        std::cout << min_heap[0] << ' ';
        std::swap(min_heap[0], min_heap[--min_heap_size]);
        SiftDown(0, min_heap_size, min_heap);
    }
}
