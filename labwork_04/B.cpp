#include <iostream>

struct Node {
  Node *parent = nullptr;
  Node *left = nullptr;
  Node *right = nullptr;
  int32_t value = 0;
};

class BST {
 private:
  Node *head = nullptr;
  Node *AddSheet(Node *current_node, Node *&next_node, int32_t value);
  Node *SearchSheet(int32_t value) const;
  Node *GetMaximumNode(Node *head) const;
 public:
  Node *GetHead() const;
  Node *GetNodeLessThen(int32_t value) const;
  Node *GetNodeMoreThen(int32_t value) const;
  Node *GetPrevNode(Node *node) const;
  void Insert(int32_t value);
  void Delete(int32_t value);
  const char *Search(int32_t value) const;
};

Node *BST::AddSheet(Node *current_node, Node *&next_node, int32_t value) {
    if (next_node != nullptr) {
        if (next_node->value == value) return nullptr;
        return next_node;
    }
    next_node = new Node;
    next_node->parent = current_node;
    next_node->value = value;
    return nullptr;
}

Node *BST::SearchSheet(int32_t value) const {
    Node *current_node = GetHead();
    while (current_node != nullptr && current_node->value != value) {
        current_node = value < current_node->value ? current_node->left : current_node->right;
    }
    return current_node;
}

Node *BST::GetMaximumNode(Node *head) const {
    while (head->right != nullptr) {
        head = head->right;
    }
    return head;
}

Node *BST::GetHead() const {
    return head;
}

Node *BST::GetNodeLessThen(int32_t value) const {
    Node *node = GetHead();
    Node *prev = nullptr;
    while (node != nullptr) {
        if (value > node->value) {
            prev = node;
            node = node->right;
        } else {
            node = node->left;
        }
    }
    return prev;
}

Node *BST::GetNodeMoreThen(int32_t value) const {
    Node *node = GetHead();
    Node *next = nullptr;
    while (node != nullptr) {
        if (value >= node->value) {
            node = node->right;
        } else {
            next = node;
            node = node->left;
        }
    }
    return next;
}

Node *BST::GetPrevNode(Node *node) const {
    if (node->left) {
        return GetMaximumNode(node->left);
    }
    Node *parent = node->parent;
    while (parent != nullptr && node == parent->left) {
        node = parent;
        parent = parent->parent;
    }
    return parent;
}

void BST::Insert(int32_t value) {
    if (head == nullptr) {
        head = new Node;
        head->value = value;
        return;
    }
    Node *curr_node = head;
    while (curr_node != nullptr) {
        curr_node = AddSheet(curr_node, value < curr_node->value ? curr_node->left : curr_node->right, value);
    }
}

void BST::Delete(int32_t value) {
    Node *node = SearchSheet(value);
    if (node == nullptr) return;
    if (node->right == nullptr && node->left == nullptr) {
        if (node->parent) {
            if (node->parent->left == node) node->parent->left = nullptr;
            else if (node->parent->right == node) node->parent->right = nullptr;
        }
        if (node->parent == nullptr) head = nullptr;
    } else if (node->right && node->left) {
        Node *prev_node = GetPrevNode(node);
        if (node->left != prev_node) {
            prev_node->left = node->left;
            if (node->left) node->left->parent = prev_node;
        }
        if (node->right != prev_node) {
            prev_node->right = node->right;
            if (node->right) node->right->parent = prev_node;
        }
        if (prev_node->parent->right == prev_node) prev_node->parent->right = nullptr;
        else prev_node->parent->left = nullptr;
        prev_node->parent = node->parent;
        if (node->parent && node->parent->right == node) node->parent->right = prev_node;
        else if (node->parent) node->parent->left = prev_node;
        if (node->parent == nullptr) {
            head = prev_node;
        }
    } else {
        if (node->parent && node->parent->left == node) {
            node->parent->left = node->right ? node->right : node->left;

        } else if (node->parent) {
            node->parent->right = node->right ? node->right : node->left;
        } else {
            head = node->right ? node->right : node->left;
        }
        if (node->left) node->left->parent = node->parent;
        else if (node->right) node->right->parent = node->parent;
    }
    delete node;
}

const char *BST::Search(int32_t value) const {
    return SearchSheet(value) ? "true" : "false";
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    uint16_t symbol;
    int32_t value;
    BST tree;
    while (std::cin >> symbol >> value) {
        if (symbol == 0) tree.Insert(value);
        else if (symbol == 1) tree.Delete(value);
        else if (symbol == 2) std::cout << tree.Search(value) << "\n";
        else if (symbol == 3) {
            Node *node = tree.GetNodeMoreThen(value);
            if (node) std::cout << node->value << "\n";
            else std::cout << "none" << "\n";
        } else if (symbol == 4) {
            Node *node = tree.GetNodeLessThen(value);
            if (node) std::cout << node->value << "\n";
            else std::cout << "none" << "\n";
        }
    }
}
