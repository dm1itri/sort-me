
#include <cstdint>
#include <cstdio>

struct Node {
  Node *next = nullptr;
  int32_t x = 0;
};

int main() {
    uint32_t n;
    char sign;
    scanf("%i", &n);
    Node *first_node = nullptr;
    Node *last_node = nullptr;

    for (size_t i = 0; i < n; i++) {
        scanf(" %c", &sign);
        if (sign == '+') {
            if (first_node) {
                last_node->next = new Node{};
                scanf("%i", &last_node->next->x);
                last_node = last_node->next;
            } else {
                last_node = new Node{};
                first_node = last_node;
                scanf("%i", &last_node->x);
            }
        } else {
            if (first_node == nullptr) continue;
            printf("%d\n", first_node->x);
            Node *first_node_next = first_node->next;
            delete first_node;
            first_node = first_node_next;
        }
    }
    return 0;
}