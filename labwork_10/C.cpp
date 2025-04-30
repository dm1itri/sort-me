#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

struct edge {
  int to, dx, dy;
};

struct point {
  int x, y;
};

int main() {
    int n;
    std::cin >> n;
    std::vector<point> cities(n);

    for (int i = 0; i < n; i++)
        std::cin >> cities[i].x >> cities[i].y;

    std::vector<std::vector<edge>> graph(n);
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) {
            int dx = cities[i].x - cities[j].x;
            int dy = cities[i].y - cities[j].y;
            graph[i].emplace_back(j, dx, dy);
            graph[j].emplace_back(i, dx, dy);
        }

    std::priority_queue<std::pair<int, std::pair<int, int>>, std::vector<std::pair<int, std::pair<int, int>>>, std::greater<>> minHeap;
    std::vector<bool> visited(n);
    std::vector<std::pair<int, int>> roads;
    double res = 0;

    minHeap.emplace(0, std::make_pair(0, -1));
    while (!minHeap.empty()) {
        auto [distance, pair] = minHeap.top();
        minHeap.pop();
        int vertexFrom = pair.first;
        int vertexTo = pair.second;

        if (visited[vertexFrom])
            continue;
        visited[vertexFrom] = true;
        if (vertexTo != -1) {
            res += pow(distance, 0.5);
            roads.emplace_back(vertexTo + 1, vertexFrom + 1);
        }

        for (const auto &edge: graph[vertexFrom])
            if (!visited[edge.to])
                minHeap.emplace(edge.dx * edge.dx + edge.dy * edge.dy, std::make_pair(edge.to, vertexFrom));
    }
    std::cout.precision(6);
    std::cout << std::fixed << res << "\n";
    std::cout << roads.size() << "\n";
    for (const std::pair<int, int> &road: roads)
        std::cout << road.first << " " << road.second << "\n";
}
