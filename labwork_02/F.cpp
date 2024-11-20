#include "iostream"
using namespace std;
void Merge(int32_t *sp, uint32_t left, uint32_t middle, uint32_t right, uint64_t *count) {
    uint32_t i = 0;
    uint32_t j = 0;
    int32_t new_sp[right - left];
    while (i + left < middle && j + middle < right) {
        if (sp[i + left] <= sp[j + middle]) {
            new_sp[i + j] = sp[i + left];
            i++;
        } else {
            *count += middle - left - i;
            new_sp[i + j] = sp[j + middle];
            j++;
        }
    }
    while (i + left < middle) {
        new_sp[i + j] = sp[i + left];
        i++;
    }
    while (j + middle < right) {
        new_sp[i + j] = sp[j + middle];
        j++;
    }
    for (size_t ii = 0; ii < right - left; ii++) {
        sp[left + ii] = new_sp[ii];
    }
}

void MergeSort(int32_t* sp, uint32_t left, uint32_t right, uint64_t *count){
    if (left + 1 >= right) {
        return;
    }
    uint32_t middle = (left + right) / 2;
    MergeSort(sp, left, middle, count);
    MergeSort(sp, middle, right, count);
    Merge(sp, left, middle, right, count);
}

int main() {
    uint32_t n;
    uint64_t count = 0;
    cin >> n;
    int32_t sp[n];
    for (int32_t &i : sp) cin >> i;
    MergeSort(sp, 0, n, &count);
    cout << count;
}