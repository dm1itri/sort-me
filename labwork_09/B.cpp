#include <iostream>
#include <vector>
#include <queue>
#include <climits>

struct Way {
  int vertexTo;
  int w;
};

std::vector<int> dijkstra(int N, int S, int F, const std::vector<std::vector<Way>> &graph) {
    std::vector<int> dist(N, INT_MAX);
    std::vector<int> prev(N, -1);
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
                prev[vertex] = u;
                pq.emplace(newDist, vertex);
            }
        }
    }

    if (dist[F] == INT32_MAX)
        return {-52};

    std::vector<int> path;
    for (int vertex = F; vertex != -1; vertex = prev[vertex])
        path.push_back(vertex);
    reverse(path.begin(), path.end());

    std::cout << dist[F] << '\n';
    return path;
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

    std::vector<int> path = dijkstra(N, S - 1, F - 1, graph);

    if (path.empty() || path[0] == -52) {
        std::cout << -1;
        return 0;
    }
    for (int i: path)
        std::cout << i + 1 << " ";
}