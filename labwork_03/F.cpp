#include <iostream>
uint16_t N;
uint16_t K;

bool check(uint32_t delta, const uint32_t *coords) {
    uint16_t count = 1;
    uint32_t last = coords[0];
    for (size_t i = 0; i < N; i++) {
        if (coords[i] - last >= delta) {
            count++;
            last = coords[i];
        }
    }
    return count >= K;
}

int main() {
    std::cin >> N >> K;
    uint32_t arr[N];
    for (uint32_t &i : arr) std::cin >> i;
    uint32_t max = arr[N - 1] - arr[0];
    uint32_t min = 0;
    uint32_t middle;
    while (max - min > 1) {
        middle = (max + min) / 2;
        if (check(middle, arr)) min = middle;
        else max = middle;
    }
    std::cout << min;
    return 0;
}