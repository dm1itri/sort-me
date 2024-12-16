#include <iostream>
int max_length = 0;
int x = 0;
int y = 0;

void UpdateMaxSize(int x_normal, int y_normal, int length) {
    if (length >= max_length) {
        max_length = length;
        x = x_normal - max_length + 2;
        y = y_normal - max_length + 2;
    }
}

int main() {
    int n, m;
    std::cin >> n >> m;
    int prev_diagonal_copy, prev_diagonal;
    int row[m];
    char symbol;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> symbol;
            prev_diagonal_copy = j == 0 || i == 0 ? 0 : prev_diagonal;
            prev_diagonal = row[j];
            if (symbol == '5') {
                if (i == 0 || j == 0) {
                    row[j] = 1;
                } else {
                    row[j] = std::min(std::min(row[j - 1], row[j]), prev_diagonal_copy) + 1;
                }
            } else {
                row[j] = 0;
            }
            UpdateMaxSize(j, i, row[j]);
        }
    }
    std::cout << max_length << ' ' << y << ' ' << x;
}
