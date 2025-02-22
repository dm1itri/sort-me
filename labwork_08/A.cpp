#include <iostream>
#include <vector>
#include <stack>

void dfs(int i, std::vector<bool>& visited, std::stack<int> &s, const std::vector<std::vector<int>> &graph) {
    visited[i] = true;
    for (int el: graph[i])
        if (!visited[el])
            dfs(el, visited, s, graph);
    s.push(i);
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int N, M;
    std::cin >> N >> M;
    std::vector<std::vector<int>> graph(N);
    for (int ii = 0; ii < M; ii++){
        int i, j;
        std::cin >> i >> j;
        graph[i-1].push_back(j-1);
    }
    std::vector<bool> visited(N, false);
    std::stack<int> s;
    for (int i = 0; i < N; i++)
        if (!visited[i])
            dfs(i, visited, s, graph);

    int res[N];
    int index = 1;
    while (!s.empty()) {
        res[s.top()] = index++;
        s.pop();
    }
    for (int value: res)
        std::cout << value << " ";
}