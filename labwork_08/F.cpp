#include <iostream>
#include <vector>
#include <queue>

void bfs(int i, std::vector<int>& visited, const std::vector<std::vector<int>> &graph) {
    std::queue<int> q;
    q.push(i);
    while(!q.empty()) {
        int current = q.front();
        q.pop();
        for (int el: graph[current]){
            if (visited[el] == -1) {
                visited[el] = visited[current] + 1;
                q.push(el);
            }
        }
    }
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int N, M, K;
    std::cin >> N >> M >> K;
    std::vector<std::vector<int>> graph(N);
    for (int ii = 0; ii < M; ii++){
        int i, j;
        std::cin >> i >> j;
        graph[i-1].push_back(j-1);
        graph[j-1].push_back(i-1);
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