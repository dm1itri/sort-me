#include <iostream>
#include <vector>
#include <stack>

void dfs(int v, std::vector<bool>& visited, const std::vector<std::vector<int>> &graph) {
    std::stack<int> stack;
    stack.push(v);
    while(!stack.empty()) {
        int current = stack.top();
        stack.pop();
        for (int vertex: graph[current]){
            if (!visited[vertex]) {
                visited[vertex] = true;
                stack.push(vertex);
            }
        }
    }
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int N, M;
    std::cin >> N >> M;
    std::vector<std::vector<int>> graph(N);
    for (int i = 0; i < M; i++){
        int vertexFrom, vertexTo;
        std::cin >> vertexFrom >> vertexTo;
        graph[vertexFrom-1].push_back(vertexTo-1);
        graph[vertexTo-1].push_back(vertexFrom-1);
    }
    std::vector<bool> visited(N);
    int count = 0;
    for (int i = 0; i < N; i++) {
        if (!visited[i]) {
            visited[i] = true;
            dfs(i, visited, graph);
            count++;
        }
    }
    std::cout << count;
}