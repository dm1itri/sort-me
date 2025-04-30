#include <iostream>
#include <vector>
#include <queue>

int prim(int n, std::vector<std::vector<std::pair<int, int>>> &graph) {
std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> minHeap;
std::vector<bool> visited(n);
int res = 0;
minHeap.emplace(0, 0);

while (!minHeap.empty()) {
std::pair<int, int> costNode = minHeap.top();
minHeap.pop();
if (visited[costNode.second])
continue;
visited[costNode.second] = true;
res += costNode.first;
for (std::pair<int, int> costNode1: graph[costNode.second])
if (!visited[costNode1.second])
minHeap.emplace(costNode1.first, costNode1.second);
}
return res;
}

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<std::pair<int, int>>> graph(n);
    for (int i = 0; i < m; i++) {
        int b, e, w;
        std::cin >> b >> e >> w;
        graph[b - 1].emplace_back(w, e - 1);
        graph[e - 1].emplace_back(w, b - 1);
    }

    std::cout << prim(n, graph);
}
