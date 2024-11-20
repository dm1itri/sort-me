#include "iostream"
using namespace std;
void Merge(int32_t *sp, uint32_t left, uint32_t middle, uint32_t right) {
    uint32_t i = 0;
    uint32_t j = 0;
    int32_t new_sp[right - left];
    while (i + left < middle && j + middle < right) {
        if (sp[i + left] <= sp[j + middle]) {
            new_sp[i + j] = sp[i + left] - j;
            i++;
        } else {
            new_sp[i + j] = sp[j + middle] + (middle - left - i);
            j++;
        }
    }
    while (i + left < middle) {
        new_sp[i + j] = sp[i + left] - (right - middle);
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

void MergeSort(int32_t *sp, uint32_t left, uint32_t right) {
    if (left + 1 >= right) {
        return;
    }
    uint32_t middle = (left + right) / 2;
    MergeSort(sp, left, middle);
    MergeSort(sp, middle, right);
    Merge(sp, left, middle, right);
}

int main() {
    uint32_t n;
    bool is_correct = true;
    cin >> n;
    int32_t sp[n];
    for (int32_t &i : sp) cin >> i;
    MergeSort(sp, 0, n);
    for (size_t i = 1; i < n; i++) {
        if (sp[i - 1] > sp[i] || sp[i - 1] < 0) {
            is_correct = false;
            break;
        }
    }
    if (is_correct) {
        for (int32_t &i : sp) cout << i << " ";
    } else cout << ":(";
}