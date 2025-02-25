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
    }
    std::vector<bool> visited(N, false);
    std::stack<int> stack;
    for (int i = 0; i < N; i++)
        if (!visited[i])
            dfs(i, visited, stack, graph);

    int res[N];
    int index = 1;
    while (!stack.empty()) {
        res[stack.top()] = index++;
        stack.pop();
    }
    for (int value : res)
        std::cout << value << " ";
}