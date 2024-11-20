#include "iostream"

using namespace std;
void InsertsSort(uint32_t *sp, uint32_t length) {
    for (size_t i = 1; i < length; i++) {
        size_t index = i;
        size_t element = sp[i];
        while (index >= 1 && element < sp[index - 1]) {
            sp[index] = sp[index - 1];
            index--;
        }
        sp[index] = element;
    }
}

int main() {
    uint32_t n;
    cin >> n;
    uint32_t sp[n];
    for (uint32_t &i : sp) cin >> i;
    InsertsSort(sp, n);
    for (uint32_t &i : sp) cout << i << " ";
}