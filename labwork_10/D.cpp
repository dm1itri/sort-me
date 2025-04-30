#include <iostream>
#include <vector>

struct City {
  int x, y;
};

int main() {
    int n;
    std::cin >> n;

    std::vector<City> cities(n);
    for (int i = 0; i < n; i++) {
        std::cin >> cities[i].x >> cities[i].y;
    }

    std::vector<bool> inMST(n);
    std::vector<double> minDist(n, INT_MAX);
    minDist[0] = 0.0;

    double res = 0.0;

    for (int i = 0; i < n; i++) {
        int u = -1;
        for (int j = 0; j < n; j++)
            if (!inMST[j] && (u == -1 || minDist[j] < minDist[u]))
                u = j;

        inMST[u] = true;
        res += minDist[u];

        for (int v = 0; v < n; v++)
            if (!inMST[v])
                minDist[v] = std::min(minDist[v], sqrt((cities[u].x - cities[v].x) * (cities[u].x - cities[v].x) + (cities[u].y - cities[v].y) * (cities[u].y - cities[v].y)));
    }

    std::cout.precision(6);
    std::cout << std::fixed << res;
}