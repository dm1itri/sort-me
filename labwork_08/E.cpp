#include <iostream>
#include <vector>

bool dfs(int v, int parent, std::vector<bool> &visited, const std::vector<std::vector<int>> &graph) {
    visited[v] = true;
    for (int vertex : graph[v]) {
        if (!visited[vertex]) {
            if (dfs(vertex, v, visited, graph))
                return true;
        } else if (vertex != parent)
            return true;
    }
    return false;
}

bool hasCycle(int N, const std::vector<std::vector<int>> &graph) {
    std::vector<bool> visited(N);
    for (int i = 0; i < N; i++)
        if (!visited[i] && dfs(i, -1, visited, graph))
            return true;
    return false;
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int N, M;
    std::cin >> N >> M;
    std::vector<std::vector<int>> graph(N);
    for (int i = 0; i < M; i++) {
        int vertexFrom, vertexTo;
        std::cin >> vertexFrom >> vertexTo;
        graph[vertexFrom - 1].push_back(vertexTo - 1);
        graph[vertexTo - 1].push_back(vertexFrom - 1);
    }
    if (hasCycle(N, graph))
        std::cout << "YES";
    else
        std::cout << "NO";
}