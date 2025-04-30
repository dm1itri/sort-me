#include <iostream>
#include <vector>
#include <queue>

struct Way {
  int vertexTo;
  int w;
};

int dijkstra(int N, int S, int F, const std::vector<std::vector<Way>> &graph) {
    std::vector<int> dist(N, INT_MAX);
    dist[S] = 0;

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq;
    pq.emplace(0, S);

    while (!pq.empty()) {
        int currentDist = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (u == F)
            break;

        if (currentDist > dist[u])
            continue;


        for (const Way &way: graph[u]) {
            int vertex = way.vertexTo;
            int newDist = currentDist + way.w;
            if (newDist < dist[vertex]) {
                dist[vertex] = newDist;
                pq.emplace(newDist, vertex);
            }
        }
    }

    if (dist[F] == INT32_MAX)
        return -1;

    return dist[F];
}

int main() {
    int N, M;
    std::cin >> N >> M;

    int S, F;
    std::cin >> S >> F;

    std::vector<std::vector<Way>> graph(N);
    for (int i = 0; i < M; i++) {
        int vertexFrom, vertexTo, w;
        std::cin >> vertexFrom >> vertexTo >> w;
        graph[vertexFrom - 1].emplace_back(vertexTo - 1, w);
        graph[vertexTo - 1].emplace_back(vertexFrom - 1, w);
    }

    std::cout <<  dijkstra(N, S - 1, F - 1, graph);
}