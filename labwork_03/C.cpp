#include <cstdint>
#include <cstdio>

void radix_sort(char *numbers, uint32_t n, uint32_t k, uint32_t index) {
    char res[n * k];
    uint32_t count[26] = {0};

    for (size_t i = 0; i < n; i++) {
        count[numbers[i * k + index] - 'a']++;
    }

    for (size_t i = 1; i < 26; i++) count[i] += count[i - 1];

    for (int32_t i = n - 1; i >= 0; i--) {
        for (size_t j = 0; j < k; j++) {
            res[(count[numbers[i * k + index] - 'a'] - 1) * k + j] = numbers[i * k + j];
        }
        count[numbers[i * k + index] - 'a']--;
    }
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < k; j++) {
            numbers[i * k + j] = res[i * k + j];
        }
    }
}

int main() {

    int32_t n;
    int32_t k;
    int32_t t;
    scanf("%d ", &n);
    scanf("%d ", &k);
    scanf("%d\n", &t);
    char numbers[n * k];
    for (size_t i = 0; i < n; i++) {
        scanf("\n%c", &numbers[i * k]);
        for (size_t j = 1; j < k; j++) {
            scanf("%c", &numbers[i * k + j]);
        }
    }

    for (int32_t i = k - 1; i >= k - t; i--) {
        radix_sort(numbers, n, k, i);
    }

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < k; j++) {
            printf("%c", numbers[i * k + j]);
        }
        printf("\n");
    }
    return 0;
}
