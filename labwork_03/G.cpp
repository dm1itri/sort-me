#include <iostream>
#define MAX(x, y) x > y ? x : y

uint64_t max_square = 0;

struct Node {
  Node *prev = nullptr;
  uint32_t index = 0;
};

Node *pop(Node *last_node) {
    Node *last_node_prev = last_node->prev;
    delete last_node;
    return last_node_prev;
}

void UpdateMaxSquare(uint32_t last_index,
                     Node *&last_node,
                     Node *node,
                     uint64_t *arr) { // ** передаем не копию указателя, а ссылку на указатель, чтобы менять значение
    uint64_t square;
    while (last_node != nullptr && (node == nullptr || arr[node->index] < arr[last_node->index])) {
        if (last_node->prev != nullptr) square = arr[last_node->index] * (last_index - last_node->prev->index - 1);
        else square = arr[last_node->index] * last_index;
        max_square = MAX(square, max_square);
        last_node = pop(last_node);
    }
}

int main() {
    uint32_t n;
    std::cin >> n;
    uint64_t arr[n];
    for (uint64_t &i : arr) std::cin >> i;
    Node *last_node = nullptr;
    for (size_t i = 0; i < n; i++) {
        Node *node = new Node;
        node->index = i;
        UpdateMaxSquare(i, last_node, node, arr);
        node->prev = last_node;
        last_node = node;
    }
    UpdateMaxSquare(n, last_node, nullptr, arr);
    std::cout << max_square;
    return 0;
}