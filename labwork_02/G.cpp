#include "iostream"
using namespace std;
void QuickSort(int32_t *sp, int32_t l, int32_t r, int32_t end) {
    int32_t i = l;
    int32_t j = r;
    int32_t middle = sp[i + rand()%(j-i)];
    while (i <= j) {
        while (sp[i] > middle) i++;
        while (sp[j] < middle) j--;
        if (i <= j ) {
            swap(sp[i], sp[j]);
            i++;
            j--;
        }
    }
    if (l < j && j > end) QuickSort(sp, l, j, end);
    if (i < r && i <= end) QuickSort(sp, i, r, end);
}

int main() {
    uint32_t n;
    uint32_t k;
    int32_t A;
    int32_t B;
    int32_t C;
    cin >> n >> k;
    int32_t c[n];
    int32_t result;
    //for (int32_t &i: c) cin >> i;
    cin >> A >> B >> C >> c[0] >> c[1];
    for (size_t i = 2; i < n; i++) c[i] = c[i-2] * A + c[i - 1] * B + C;
    QuickSort(c, 0, n - 1, k-1);
    result = c[0];
    for (int32_t i = 1; i < k; i++) result ^= c[i];

    cout << result;
}