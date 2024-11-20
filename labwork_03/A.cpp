#include <iostream>
using namespace std;

struct Node {
  Node *prev = nullptr;
  int32_t x = 0;
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    uint32_t n;
    char sign;
    cin >> n;
    cin >> sign;
    Node *last_node = new Node;
    cin >> last_node->x;
    for (size_t i = 1; i < n; i++) {
        cin >> sign;
        if (sign == '+') {
            Node *new_node = new Node;
            new_node->prev = last_node;
            cin >> new_node->x;
            last_node = new_node;
        } else {
            if (last_node == nullptr) continue;
            cout << last_node->x << '\n';
            Node *last_node_prev = last_node->prev;
            delete last_node;
            last_node = last_node_prev;
        }
    }
    return 0;
}