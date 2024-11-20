#include "iostream"
using namespace std;
int main() {
    uint32_t n;
    cin >> n;
    uint32_t sp[n];
    uint32_t a;
    sp[0] = 1;
    sp[1] = 2;
    for (size_t i = 2; i < n; i++) {
        a = i + 1;
        sp[i] = sp[i / 2];
        sp[i / 2] = a;
    }
    for (uint32_t &i : sp) cout << i << " ";
}