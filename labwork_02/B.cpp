#include "iostream"
using namespace std;

void QuickSort(int32_t *sp, int32_t l, int32_t r) {
    int32_t i = l;
    int32_t j = r;
    int32_t middle = (sp[i] + sp[j]) / 2;
    while (i <= j) {
        while (sp[i] < middle) i++;
        while (sp[j] > middle) j--;
        if (i <= j) {
            swap(sp[i], sp[j]);
            i++;
            j--;
        }
    }
    if (l < j) QuickSort(sp, l, j);
    if (i < r) QuickSort(sp, i, r);
}

int main() {
    uint32_t n;
    cin >> n;
    int32_t sp[n];
    for (int32_t &i : sp) cin >> i;
    QuickSort(sp, 0, n - 1);
    for (int32_t &i : sp) cout << i << " ";
}
