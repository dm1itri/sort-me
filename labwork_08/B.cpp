#include <iostream>
#include <vector>
#include <stack>

void dfs(int v, const std::vector<std::vector<int>> &graph, std::vector<bool> &visited, std::stack<int> &stack) {
    visited[v] = true;
    for (int vertex : graph[v]) {
        if (!visited[vertex]) {
            dfs(vertex, graph, visited, stack);
        }
    }
    stack.push(v);
}

void dfs(int v, const std::vector<std::vector<int>> &graph, std::vector<bool> &visited, std::vector<int> &componentID, int componentCount) {
    visited[v] = true;
    for (int vertex : graph[v]) {
        if (!visited[vertex]) {
            dfs(vertex, graph, visited, componentID, componentCount);
        }
    }
    componentID[v] = componentCount;
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int n, m, q;
    std::cin >> n >> m >> q;
    std::vector<std::vector<int>> graph(n), transposeGraph(n);
    for (int ii = 0; ii < m; ii++) {
        int i, j;
        std::cin >> i >> j;
        graph[i - 1].push_back(j - 1);
        transposeGraph[j - 1].push_back(i - 1);
    }

    std::stack<int> stack;
    std::vector<bool> visited(n, false);
    for (int vertex = 0; vertex < n; vertex++) {
        if (!visited[vertex]) {
            dfs(vertex, graph, visited, stack);
        }
    }

    std::vector<int> componentID(n, -1);
    int componentCount = 0;
    fill(visited.begin(), visited.end(), false);

    while (!stack.empty()) {
        int vertex = stack.top();
        stack.pop();
        if (!visited[vertex]) {
            dfs(vertex, transposeGraph, visited, componentID, componentCount);
            componentCount++;
        }
    }

    for (int i = 0; i < q; i++) {
        int a, b;
        std::cin >> a >> b;
        if (componentID[a-1] == componentID[b-1])
            std::cout << "YES\n";
        else
            std::cout << "NO\n";
    }
}