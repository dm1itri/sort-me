#include <iostream>

struct Node {
  Node *left = nullptr;
  Node *right = nullptr;
  int32_t value = 0;
};

class BST {
 private:
  Node *head;
  Node *AddSheet(Node *&next_node, int32_t value);
 public:
  BST(int32_t value);
  Node *GetHead() const;
  void Insert(int32_t value);
  void PrintAscending(Node *node);
};

Node *BST::AddSheet(Node *&next_node, int32_t value) {
    if (next_node != nullptr) return next_node;
    Node *new_node = new Node;
    new_node->value = value;
    next_node = new_node;
    return nullptr;
}

BST::BST(int32_t value) {
    head = new Node;
    head->value = value;
}

Node *BST::GetHead() const {
    return head;
}

void BST::Insert(int32_t value) {
    Node *current_node = head;
    while (current_node != nullptr) {
        current_node = AddSheet(value > current_node->value ? current_node->right : current_node->left, value);
    }
}

void BST::PrintAscending(Node *node) {
    if (node != nullptr) {
        PrintAscending(node->left);
        std::cout << node->value << " ";
        PrintAscending(node->right);
    }
}

int main() {
    uint32_t n;
    std::cin >> n;
    int32_t value;
    std::cin >> value;
    BST tree(value);
    for (size_t i = 1; i < n; i++) {
        std::cin >> value;
        tree.Insert(value);
    }
    tree.PrintAscending(tree.GetHead());
}