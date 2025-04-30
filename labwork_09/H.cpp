#include <iostream>

int main() {
    int N, M;
    std::cin >> N >> M;
    for (int i = 0; i < N; i++)
        for (int j = i + 1; j < N && 0 < M; j++ && M--)
            std::cout << i + 1 << ' ' << j + 1 << ' ' << j - i - 1 << '\n';
}