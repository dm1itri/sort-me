#include <iostream>
#include <vector>

bool dfs(int i, int parent, std::vector<bool> &visited, const std::vector<std::vector<int>> &graph) {
    visited[i] = true;
    for (int el : graph[i]) {
        if (!visited[el]) {
            if (dfs(el, i, visited, graph))
                return true;
        } else if (el != parent)
            return true;
    }
    return false;
}

bool hasCycle(int N, const std::vector<std::vector<int>> &graph) {
    std::vector<bool> visited(N, false);
    for (int i = 0; i < N; ++i) {
        if (!visited[i] && dfs(i, -1, visited, graph))
            return true;
    }
    return false;
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int N, M;
    std::cin >> N >> M;
    std::vector<std::vector<int>> graph(N);
    for (int ii = 0; ii < M; ii++) {
        int i, j;
        std::cin >> i >> j;
        graph[i - 1].push_back(j - 1);
        graph[j - 1].push_back(i - 1);
    }
    if (hasCycle(N, graph))
        std::cout << "YES";
    else
        std::cout << "NO";
}