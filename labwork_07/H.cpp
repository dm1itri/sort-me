#include <iostream>
#include <cmath>

void PrintBin(int value, int length) {
    char arr[length+2];
    for (size_t i = 0; i < length; i++) arr[i] = '0';
    arr[length] = '\n';
    arr[length+1] = '\0';
    for (int i = 0; value > 0; i++) {
        arr[length - i - 1] = value % 2 + '0';
        value >>= 1;
    }
    std::cout << arr;
}

int main() {
    int n;
    std::cin >> n;
    for (int i = 0; i < pow(2, n); i++) {
        PrintBin(i ^ (i >> 1), n);
    }
}
