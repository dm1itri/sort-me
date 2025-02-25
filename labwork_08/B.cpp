#include <iostream>
#include <vector>
#include <stack>

void dfs(int v, std::vector<bool> &visited, std::stack<int> &stack, const std::vector<std::vector<int>> &graph) {
    visited[v] = true;
    for (int vertex : graph[v])
        if (!visited[vertex])
            dfs(vertex, visited, stack, graph);
    stack.push(v);
}

void dfs(int v, std::vector<bool> &visited, std::vector<int> &componentID, int componentCount, const std::vector<std::vector<int>> &graph) {
    visited[v] = true;
    for (int vertex : graph[v])
        if (!visited[vertex])
            dfs(vertex, visited, componentID, componentCount, graph);
    componentID[v] = componentCount;
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int n, m, q;
    std::cin >> n >> m >> q;
    std::vector<std::vector<int>> graph(n), revGraph(n);
    for (int ii = 0; ii < m; ii++) {
        int vertexFrom, vertexTo;
        std::cin >> vertexFrom >> vertexTo;
        graph[vertexFrom - 1].push_back(vertexTo - 1);
        revGraph[vertexTo - 1].push_back(vertexFrom - 1);
    }

    std::stack<int> stack;
    std::vector<bool> visited(n);
    for (int vertex = 0; vertex < n; vertex++)
        if (!visited[vertex])
            dfs(vertex, visited, stack, graph);

    int componentCount = 0;
    std::vector<int> componentID(n);
    fill(visited.begin(), visited.end(), false);

    while (!stack.empty()) {
        int vertex = stack.top();
        stack.pop();
        if (!visited[vertex]) {
            dfs(vertex, visited, componentID, componentCount, revGraph);
            componentCount++;
        }
    }

    for (int i = 0; i < q; i++) {
        int vertexFrom, vertexTo;
        std::cin >> vertexFrom >> vertexTo;
        if (componentID[vertexFrom - 1] == componentID[vertexTo - 1])
            std::cout << "YES\n";
        else
            std::cout << "NO\n";
    }
}