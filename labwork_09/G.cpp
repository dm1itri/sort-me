#include <iostream>
#include <vector>

int main() {
    int N;
    std::cin >> N;
    std::vector<std::vector<int>> dist(N, std::vector<int>(N, INT32_MAX));

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++){
            int time;
            std::cin >> time;
            if (time != -1)
                dist[i][j] = time;
        }

    for (int k = 0; k < N; k++)
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                if (dist[i][k] != INT32_MAX && dist[k][j] != INT32_MAX)
                    dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);

    std::vector<int> ex(N);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (dist[i][j] != INT32_MAX && dist[i][j] > ex[i])
                ex[i] = dist[i][j];

    std::cout << *max_element(ex.begin(), ex.end()) << '\n';
    std::cout << *min_element(ex.begin(), ex.end());;
}