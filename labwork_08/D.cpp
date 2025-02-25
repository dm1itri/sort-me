#include <iostream>
#include <vector>
#include <set>

void dfs(int v, std::vector<bool> &visited, std::vector<int> &order, const std::vector<std::vector<int>> &graph) {
    visited[v] = true;
    for (int vertex : graph[v])
        if (!visited[vertex])
            dfs(vertex, visited, order, graph);
    order.push_back(v);
}

void dfs(int v, int comp, std::vector<int> &component, std::vector<std::vector<int>> &components, const std::vector<std::vector<int>> &graph) {
    component[v] = comp;
    components[comp].push_back(v);
    for (int vertex : graph[v])
        if (component[vertex] == -1)
            dfs(vertex, comp, component, components, graph);
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    int N, M;
    std::cin >> N >> M;
    std::vector<std::vector<int>> graph(N);
    std::vector<std::vector<int>> graphRev(N);
    for (int i = 0; i < M; i++) {
        int vertexFrom, vertexTo;
        std::cin >> vertexFrom >> vertexTo;
        graph[vertexFrom - 1].push_back(vertexTo - 1);
        graphRev[vertexTo - 1].push_back(vertexFrom - 1);
    }

    std::vector<int> order;
    std::vector<bool> visited(N);
    for (int v = 0; v < N; v++)
        if (!visited[v])
            dfs(v, visited, order, graph);

    int compCount = 0;
    std::vector<int> component(N, -1);
    std::vector<std::vector<int>> components(N);
    for (int i = order.size() - 1; i >= 0; i--)
        if (component[order[i]] == -1)
            dfs(order[i], compCount++, component, components, graphRev);

    std::vector<int> family(N);
    for (int i = 0; i < compCount; i++) {
        int minHouse = *std::min_element(components[i].begin(), components[i].end());
        for (int v : components[i])
            family[v] = minHouse;
    }
    std::set<std::pair<int, int>> res;
    for (int vertexFrom = 0; vertexFrom < N; vertexFrom++)
        for (int vertexTo : graph[vertexFrom])
            if (family[vertexFrom] != family[vertexTo])
                res.emplace(family[vertexFrom] + 1, family[vertexTo] + 1);

    std::cout << compCount << ' ' << res.size() << '\n';
    for (const std::pair<int, int> &road : res)
        std::cout << road.first << ' ' << road.second << '\n';
}