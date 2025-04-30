#include <iostream>
#include <vector>

struct Way {
  int vertexTo;
  int w;
};

void dfs(int vertexFrom, std::vector<bool> &visited, const std::vector<std::vector<Way>> &graph) {
    visited[vertexFrom] = true;
    for (const Way &way: graph[vertexFrom])
        if (!visited[way.vertexTo])
            dfs(way.vertexTo, visited, graph);
}

bool checkCycle(int n, const std::vector<int> &dist, const std::vector<std::vector<Way>> &graph) {
    std::vector<bool> inCycle(n, false);

    for (int vertexFrom = 0; vertexFrom < n; vertexFrom++)
        if (dist[vertexFrom] != INT_MIN)
            for (const Way &way: graph[vertexFrom])
                if (dist[way.vertexTo] < dist[vertexFrom] + way.w)
                    inCycle[way.vertexTo] = true;

    for (int i = 0; i < n; i++)
        if (inCycle[i])
            dfs(i, inCycle, graph);
    return inCycle[n - 1];
}


int main() {
    int N, M;
    std::cin >> N >> M;

    std::vector<std::vector<Way>> graph(N);
    for (int i = 0; i < M; i++) {
        int vertexFrom, vertexTo, w;
        std::cin >> vertexFrom >> vertexTo >> w;
        graph[vertexFrom - 1].emplace_back(vertexTo - 1, w);
    }
    std::vector<int> dist(N, INT_MIN);
    dist[0] = 0;
    for (int i = 0; i < N - 1; i++)
        for (int vertexFrom = 0; vertexFrom < N; vertexFrom++)
            if (dist[vertexFrom] != INT_MIN)
                for (const Way &way: graph[vertexFrom])
                    if (dist[way.vertexTo] < dist[vertexFrom] + way.w)
                        dist[way.vertexTo] = dist[vertexFrom] + way.w;

    if (dist[N - 1] == INT_MIN)
        std::cout << ":(";
    else if (checkCycle(N, dist, graph))
        std::cout << ":)";
    else
        std::cout << dist[N - 1];
}