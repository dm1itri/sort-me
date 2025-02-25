#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <array>

struct Point {
  int x;
  int y;
  int z;
};

const int SIZE = 102;

bool isValid(int x, int y, int z, const std::array<std::array<std::array<int, SIZE>, SIZE>, SIZE> &area) {
    return 0 <= x && x < SIZE && 0 <= y && y < SIZE && 0 <= z && z < SIZE && area[z][y][x] != -1;
}

int dijkstra(const Point &start, const Point &finish, std::array<std::array<std::array<int, SIZE>, SIZE>, SIZE> &area) {
    area[start.z][start.y][start.x] = 0;
    std::priority_queue<std::tuple<int, int, int, int>, std::vector<std::tuple<int, int, int, int>>, std::greater<>> pq;
    pq.emplace(0, start.x, start.y, start.z);

    int dx[6] = {-1, 1, 0, 0, 0, 0};
    int dy[6] = {0, 0, -1, 1, 0, 0};
    int dz[6] = {0, 0, 0, 0, -1, 1};

    while (!pq.empty()) {
        auto [currentDist, x, y, z] = pq.top();
        pq.pop();
        if (x == finish.x && y == finish.y && z == finish.z)
            return currentDist;
        for (int i = 0; i < 6; i++) {
            int new_x = x + dx[i];
            int new_y = y + dy[i];
            int new_z = z + dz[i];
            if (!isValid(new_x, new_y, new_z, area))
                continue;
            int newDist = currentDist + 1;
            if (newDist < area[new_z][new_y][new_x]) {
                area[new_z][new_y][new_x] = newDist;
                pq.emplace(newDist, new_x, new_y, new_z);
            }
        }
    }
    return -1;
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int K, E;
    std::cin >> K >> E;
    Point start, finish;
    std::cin >> start.x >> start.y >> start.z;
    std::cin >> finish.x >> finish.y >> finish.z;

    std::array<std::array<std::array<int, SIZE>, SIZE>, SIZE> area;
    for (int z = 0; z < SIZE; z++)
        for (int y = 0; y < SIZE; y++)
            for (int x = 0; x < SIZE; x++)
                area[z][y][x] = INT_MAX;

    for (int i = 0; i < K; i++) {
        int x, y, z, h;
        std::cin >> x >> y >> z >> h;
        for (int j = 0; j < h; j++)
            area[z + j][y][x] = -1;
    }
    if (start.x == finish.x && start.y == finish.y && start.z == finish.z)
        std::cout << 0;
    else if (area[start.z][start.y][start.x] == -1 || area[finish.z][finish.y][finish.x] == -1)
        std::cout << -1;
    else {
        int res = dijkstra(start, finish, area);
        if (res == -1 || res > E)
            std::cout << -1;
        else
            std::cout << res;
    }
}