#include <iostream>
#include <vector>

struct Way {
  int vertexTo;
  long long w;
};

void dfs(int vertexFrom, std::vector<bool> &visited, const std::vector<std::vector<Way>> &graph) {
    visited[vertexFrom] = true;
    for (const Way &way: graph[vertexFrom])
        if (!visited[way.vertexTo])
            dfs(way.vertexTo, visited, graph);
}

void checkCycle(int n, std::vector<bool> &inCycle, const std::vector<long long> &dist, const std::vector<std::vector<Way>> &graph) {
    for (int vertexFrom = 0; vertexFrom < n; vertexFrom++)
        if (dist[vertexFrom] != LLONG_MAX)
            for (const Way &way: graph[vertexFrom])
                if (dist[way.vertexTo] > dist[vertexFrom] + way.w)
                    inCycle[way.vertexTo] = true;

    for (int i = 0; i < n; i++)
        if (inCycle[i])
            dfs(i, inCycle, graph);
}


int main() {
    int N, M, S;
    std::cin >> N >> M >> S;
    S--;
    std::vector<std::vector<Way>> graph(N);
    for (int i = 0; i < M; i++) {
        int vertexFrom, vertexTo;
        long long w;
        std::cin >> vertexFrom >> vertexTo >> w;
        graph[vertexFrom - 1].emplace_back(vertexTo - 1, w);
    }
    std::vector<long long> dist(N, LLONG_MAX);
    dist[S] = 0;
    for (int i = 0; i < N - 1; i++)
        for (int vertexFrom = 0; vertexFrom < N; vertexFrom++)
            if (dist[vertexFrom] != LLONG_MAX)
                for (const Way &way: graph[vertexFrom])
                    if (dist[way.vertexTo] > dist[vertexFrom] + way.w)
                        dist[way.vertexTo] = dist[vertexFrom] + way.w;

    std::vector<bool> inCycle(N);
    checkCycle(N, inCycle, dist, graph);

    for (int i = 0; i < N; i++)
        if (dist[i] == LLONG_MAX)
            std::cout << "*\n";
        else if (inCycle[i])
            std::cout << "-\n";
        else
            std::cout << dist[i] << '\n';
}