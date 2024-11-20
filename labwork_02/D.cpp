#include "iostream"
using namespace std;
void Merge(int32_t (*sp)[2], uint32_t left, uint32_t middle, uint32_t right) {
    uint32_t i = 0;
    uint32_t j = 0;
    int32_t new_sp[right - left][2];
    while (i + left < middle && j + middle < right) {
        if (sp[i + left][0] < sp[j + middle][0]
            || sp[i + left][0] == sp[j + middle][0] && sp[i + left][1] >= sp[j + middle][1]) {
            new_sp[i + j][0] = sp[i + left][0];
            new_sp[i + j][1] = sp[i + left][1];
            i++;
        } else {
            new_sp[i + j][0] = sp[j + middle][0];
            new_sp[i + j][1] = sp[j + middle][1];
            j++;
        }
    }
    while (i + left < middle) {
        new_sp[i + j][0] = sp[i + left][0];
        new_sp[i + j][1] = sp[i + left][1];
        i++;
    }
    while (j + middle < right) {
        new_sp[i + j][0] = sp[j + middle][0];
        new_sp[i + j][1] = sp[j + middle][1];
        j++;
    }
    for (size_t ii = 0; ii < right - left; ii++) {
        sp[left + ii][0] = new_sp[ii][0];
        sp[left + ii][1] = new_sp[ii][1];
    }
}

void MergeSort(int32_t (*sp)[2], uint32_t left, uint32_t right) {
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

    cin >> n;
    int32_t sp[n][2];
    for (size_t i = 0; i < n; i++) {
        cin >> sp[i][0] >> sp[i][1];
    }
    MergeSort(sp, 0, n);
    uint64_t count = sp[0][1] - sp[0][0] + 1;
    uint64_t last_zabor = sp[0][1];
    for (size_t i = 1; i < n; i++) {
        if (sp[i][0] >= sp[i - 1][0] + 1 && last_zabor < sp[i][1]) {
            if (last_zabor >= sp[i][0]) count += sp[i][1] - last_zabor;
            else count += sp[i][1] - sp[i][0] + 1;
            last_zabor = sp[i][1];
        }
    }
    cout << count;
}