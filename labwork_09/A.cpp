#include <iostream>
#include <vector>
#include <queue>


int dijkstra(int N, int S, int F, const std::vector<std::vector<int>>& graph) {
    std::vector<int> dist(N, INT_MAX);
    dist[S] = 0;
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq;
    pq.emplace(0, S);

    while (!pq.empty()) {
        int currentDist = pq.top().first;
        int vertex = pq.top().second;
        pq.pop();

        if (vertex == F)
            return currentDist;

        if (currentDist > dist[vertex])
            continue;

        for (int v = 0; v < N; v++) {
            if (graph[vertex][v] != -1) {
                int new_time = currentDist + graph[vertex][v];
                if (new_time < dist[v]) {
                    dist[v] = new_time;
                    pq.emplace(new_time, v);
                }
            }
        }
    }
    return -1;
}

int main() {
    int N, S, F;
    std::cin >> N >> S >> F;

    std::vector<std::vector<int>> graph(N, std::vector<int>(N));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            std::cin >> graph[i][j];

    int result = dijkstra(N, S-1, F-1, graph);
    std::cout << result;
}