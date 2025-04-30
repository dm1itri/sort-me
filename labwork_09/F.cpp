#include <iostream>
#include <vector>


struct Exchange {
  int a;
  int b;
  double rate;
  double commission;
};


int main() {
    int n, m, s;
    double v;
    std::cin >> n >> m >> s >> v;

    std::vector<Exchange> exchanges;
    for (int i = 0; i < m; i++) {
        int a, b;
        double r_ab, c_ab, r_ba, c_ba;
        std::cin >> a >> b >> r_ab >> c_ab >> r_ba >> c_ba;
        exchanges.emplace_back(a, b, r_ab, c_ab);
        exchanges.emplace_back(b, a, r_ba, c_ba);
    }

    std::vector<double> dist(n + 1, 0);
    dist[s] = v;

    for (int i = 0; i < n; i++)
        for (const Exchange& e : exchanges)
            if (0 < dist[e.a] && dist[e.b] < (dist[e.a] - e.commission) * e.rate) {
                if (i == n - 1) {
                    std::cout << "YES";
                    return 0;
                }
                dist[e.b] = (dist[e.a] - e.commission) * e.rate;
            }
    std::cout << "NO";
}