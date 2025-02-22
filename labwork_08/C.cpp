#include <iostream>
#include <vector>
#include <stack>

void dfs(int i, std::vector<bool>& visited, const std::vector<std::vector<int>> &graph) {
    std::stack<int> s;
    s.push(i);
    while(!s.empty()) {
        int current = s.top();
        s.pop();
        for (int el: graph[current]){
            if (!visited[el]) {
                visited[el] = true;
                s.push(el);
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
    for (int ii = 0; ii < M; ii++){
        int i, j;
        std::cin >> i >> j;
        graph[i-1].push_back(j-1);
        graph[j-1].push_back(i-1);
    }
    std::vector<bool> visited(N, false);
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