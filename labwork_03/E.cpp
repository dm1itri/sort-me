#include <iostream>
using namespace std;

struct MyPair {
  uint32_t first;
  uint32_t second;
  double result;
};

void QuickSort(MyPair *sp, int32_t l, int32_t r) {
    int32_t i = l;
    int32_t j = r;
    double middle = (sp[i].result + sp[j].result) / 2;
    while (i <= j) {
        while (sp[i].result < middle) i++;
        while (sp[j].result > middle) j--;
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
    uint32_t N;
    uint32_t K;
    cin >> N >> K;
    uint32_t numbers[N];
    for (uint32_t &i : numbers) cin >> i;
    MyPair arr[N * (N - 1) / 2];
    uint32_t index = 0;
    for (size_t i = 0; i < N - 1; i++) {
        for (size_t j = i + 1; j < N; j++) {
            arr[index].first = numbers[i];
            arr[index].second = numbers[j];
            arr[index].result = double(numbers[i]) / double(numbers[j]);
            index++;
        }
    }
    QuickSort(arr, 0, N * (N - 1) / 2 - 1);
    printf("%d %d", arr[K - 1].first, arr[K - 1].second);

    return 0;
}
