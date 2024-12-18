#include <iostream>

int BinarySearch(int *data, int length, int value) {
    int l = 0;
    int r = length;
    while (l <= r) {
        int mid = (r + l) / 2;
        if (data[mid] < value) {
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    return l;
}

int main() {
    int n;
    int max_length = 1;
    std::cin >> n;
    int heights[n];
    for (int &i : heights) std::cin >> i;
    int lens[n];
    lens[0] = heights[0];
    for (int i = 1; i < n; i++) {
        if (heights[i] > lens[max_length - 1]) {
            lens[max_length++] = heights[i];
        } else {
            int index = BinarySearch(lens, max_length, heights[i]);
            lens[index] = heights[i];
        }
    }
    std::cout << max_length;
}
