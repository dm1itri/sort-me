#include "iostream"
using namespace std;
void Merge(int32_t *sp, uint32_t left, uint32_t middle, uint32_t right) {
    uint32_t i = 0;
    uint32_t j = 0;
    int32_t new_sp[right - left];
    while (i + left < middle && j + middle < right) {
        if (sp[i + left] <= sp[j + middle]) {
            new_sp[i + j] = sp[i + left];
            i++;
        } else {
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
    int32_t n;
    cin >> n;
    int32_t sp[n];
    for (int32_t &i : sp) cin >> i;
    MergeSort(sp, 0, n);
    uint32_t last_element = sp[n - 1];
    uint64_t first_side = 0;
    uint64_t second_side = 0;
    uint64_t square = 0;
    for (int32_t i = n - 2; i >= 0; i--) {
        if (last_element == sp[i] || last_element == sp[i] + 1) {
            if (first_side == 0 && last_element) {
                first_side = sp[i];
                last_element = 0;
            } else if (second_side == 0 && last_element) {
                second_side = sp[i];
                last_element = 0;
            }
        } else {
            last_element = sp[i];
        }
        if (first_side && second_side) {
            square += first_side * second_side;
            first_side = 0;
            second_side = 0;
        }
    }
    cout << square;
}