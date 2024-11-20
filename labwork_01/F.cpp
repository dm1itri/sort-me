#include "iostream"
using namespace std;

int64_t convert(int16_t &ii, int16_t &jj, int16_t &ll) {
    int64_t multiplier = 2, res = 1;
    for (int16_t i = 1; i < ll; ++i) {
        res += multiplier;
        multiplier *= 2;
    }
    for (int16_t i = 0; i < jj; ++i) multiplier *= 2;
    for (int16_t i = 0; i < ii; ++i) {
        res += multiplier;
        multiplier *= 2;
    }
    return res;
}

int main() {
    int64_t x, y, number, count = 0;
    cin >> x >> y;
    for (int16_t i = 1; i <= 60; ++i) { // 2*59 < 10**18 < 2**60
        for (int16_t j = 1; j <= 60 - i; ++j) {
            for (int16_t l = 1; l <= 60 - i - j; ++l) {
                number = convert(i, j, l);
                if (x <= number && number <= y) count++;
            }
        }

    }
    cout << count;
}