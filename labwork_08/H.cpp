#include <iostream>
#include <vector>
#include <stack>

void addImplication(int vertexFrom, int vertexTo, std::vector<std::vector<int>> &graph, std::vector<std::vector<int>> &graphRev) {
    graph[vertexFrom].push_back(vertexTo);
    graphRev[vertexTo].push_back(vertexFrom);
}

void dfs(int v, const std::vector<std::vector<int>> &graph, std::vector<bool> &visited, std::stack<int> &order) {
    visited[v] = true;
    for (int vertex : graph[v])
        if (!visited[vertex])
            dfs(vertex, graph, visited, order);
    order.push(v);
}

void dfs(int v, int comp, const std::vector<std::vector<int>> &graph, std::vector<int> &component) {
    component[v] = comp;
    for (int vertex : graph[v])
        if (component[vertex] == -1)
            dfs(vertex, comp, graph, component);
}

bool solve2SAT(int n, std::vector<std::vector<int>> &graph, std::vector<std::vector<int>> &graphRev) {
    std::vector<bool> visited(n * 2);
    std::stack<int> stack;

    for (int i = 0; i < 2 * n; i++)
        if (!visited[i])
            dfs(i, graph, visited, stack);

    int currComp = 0;
    std::vector<int> component(n * 2, -1);
    while (!stack.empty()) {
        int vertex = stack.top();
        stack.pop();
        if (component[vertex] == -1)
            dfs(vertex, currComp++, graphRev, component);
    }

    for (int i = 0; i < n; i++)
        if (component[i] == component[i + n])
            return false;
    return true;
}

int main() {
    int n, k;
    std::cin >> n >> k;
    std::vector<std::vector<int>> graph(n * 2);
    std::vector<std::vector<int>> graphRev(n * 2);
    std::string s;
    getline(std::cin, s);

    for (int i = 0; i < k; i++) {
        getline(std::cin, s);
        if (s[0] == '!') {
            int vertexFrom = stoi(s.substr(1)) - 1;
            addImplication(vertexFrom, vertexFrom + n, graph, graphRev);
        } else {
            int vertexFrom = stoi(s.substr(0, s.find_first_of(' '))) - 1;
            char type = s[s.find_first_of(' ') + 1];
            int vertexTo = stoi(s.substr(s.find_last_of(' ') + 1)) - 1;
            if (type == '|') {  // A || B эквивалентно !A -> B и !B -> A
                addImplication(vertexFrom + n, vertexTo, graph, graphRev);
                addImplication(vertexTo + n, vertexFrom, graph, graphRev);
            } else if (type == '-') {  // A -> B эквивалентно !A || B
                addImplication(vertexFrom, vertexTo, graph, graphRev);
                addImplication(vertexTo + n, vertexFrom + n, graph, graphRev);
            } else if (type == '&') {  // A && B эквивалентно A и B
                addImplication(vertexFrom + n, vertexFrom, graph, graphRev);
                addImplication(vertexTo + n, vertexTo, graph, graphRev);
            } else if (type == '^') {  // A ^ B эквивалентно (A || B) && (!A || !B)
                addImplication(vertexFrom + n, vertexTo, graph, graphRev);
                addImplication(vertexTo + n, vertexFrom, graph, graphRev);
                addImplication(vertexFrom, vertexTo + n, graph, graphRev);
                addImplication(vertexTo, vertexFrom + n, graph, graphRev);
            }
        }
    }

    if (solve2SAT(n, graph, graphRev))
        std::cout << "YES";
    else
        std::cout << "NO";
}