#include <iostream>

int main() {
    int n;
    std::cin >> n;
    int arr[n];
    for (int &i : arr) std::cin >> i;
    int left, right;
    const char *res = "YES";
    for (int i = 0; i < n; i++) {
        left = 2 * i + 1;
        right = 2 * i + 2;
        if (left < n && arr[left] < arr[i] || right < n && arr[right] < arr[i])
            res = "NO";
    }
    std::cout << res;
}