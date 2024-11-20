#include <iostream>

struct Node {
  Node *left = nullptr;
  Node *right = nullptr;
  int32_t value = 0;
  uint16_t level = 0;
};

Node *arr[1000] = {nullptr};

class BST {
 private:
  Node *head = nullptr;
  Node *AddSheet(Node *current_node, Node *&next_node, int32_t value, uint16_t level);
 public:
  Node *GetHead() const;
  void Insert(int32_t value);
  void PrintAscending(Node *node);
};

Node *BST::AddSheet(Node *current_node, Node *&next_node, int32_t value, uint16_t level) {
    if (next_node != nullptr) {
        if (next_node->value == value) return nullptr;
        return next_node;
    }
    if (current_node->value == value) return nullptr;
    next_node = new Node;
    next_node->value = value;
    next_node->level = level;
    return nullptr;
}

Node *BST::GetHead() const {
    return head;
}

void BST::Insert(int32_t value) {
    if (head == nullptr) {
        head = new Node;
        head->value = value;
        return;
    }
    Node *curr_node = head;
    uint16_t level = 1;
    while (curr_node != nullptr) {
        curr_node = AddSheet(curr_node, value < curr_node->value ? curr_node->left : curr_node->right, value, level++);
    }
}

void BST::PrintAscending(Node *node) {
    if (node != nullptr) {
        PrintAscending(node->left);
        arr[node->level] = node;
        PrintAscending(node->right);
    }
}

int main() {
    uint32_t n;
    std::cin >> n;
    int32_t value;
    BST tree;
    for (size_t i = 0; i < n; i++) {
        std::cin >> value;
        tree.Insert(value);
    }
    tree.PrintAscending(tree.GetHead());
    for (Node *node : arr) {
        if (node) std::cout << node->value << ' ';
    }
}