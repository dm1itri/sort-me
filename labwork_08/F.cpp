#include <iostream>
#include <vector>
#include <queue>

void bfs(int v, std::vector<int> &visited, const std::vector<std::vector<int>> &graph) {
    std::queue<int> queue;
    queue.push(v);
    while (!queue.empty()) {
        int currentVertex = queue.front();
        queue.pop();
        for (int vertex : graph[currentVertex])
            if (visited[vertex] == -1) {
                visited[vertex] = visited[currentVertex] + 1;
                queue.push(vertex);
            }
    }
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int N, M, K;
    std::cin >> N >> M >> K;
    std::vector<std::vector<int>> graph(N);
    for (int i = 0; i < M; i++) {
        int vertexFrom, vertexTo;
        std::cin >> vertexFrom >> vertexTo;
        graph[vertexFrom - 1].push_back(vertexTo - 1);
        graph[vertexTo - 1].push_back(vertexFrom - 1);
    }
    std::vector<int> visited(N, -1);
    visited[0] = 0;
    bfs(0, visited, graph);

    bool found = false;
    for (int i = 0; i < N; i++)
        if (visited[i] == K) {
            found = true;
            std::cout << i + 1 << '\n';
        }
    if (!found)
        std::cout << "NO";
}