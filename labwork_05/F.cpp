#include <iostream>

struct Node {
  Node *left = nullptr;
  Node *right = nullptr;
  int value = 0;
  int height = 0;
};

int GetHeight(Node *node) {
    return node ? node->height : 0;
}

int GetMaxHeight(Node *node) {
    return std::max(GetHeight(node->left), GetHeight(node->right)) + 1;
}

int GetBalance(Node *node) {
    return node ? GetHeight(node->right) - GetHeight(node->left) : 0;
}

Node *LeftRotate(Node *node) {
    Node *node_copy = node->right;
    node->right = node_copy->left;
    node_copy->left = node;
    node->height = GetMaxHeight(node);
    node_copy->height = GetMaxHeight(node_copy);
    return node_copy;
}

Node *RightRotate(Node *node) {
    Node *node_copy = node->left;
    node->left = node_copy->right;
    node_copy->right = node;
    node->height = GetMaxHeight(node);
    node_copy->height = GetMaxHeight(node_copy);
    return node_copy;
}

Node *Balance(Node *root) {
    int balance = GetBalance(root);
    if (balance == -2) {
        if (GetBalance(root->left) == 1) {
            root->left = LeftRotate(root->left);
        }
        return RightRotate(root);
    } else if (balance == 2) {
        if (GetBalance(root->right) == -1) {
            root->right = RightRotate(root->right);
        }
        return LeftRotate(root);
    }
    return root;
}

Node *Insert(Node *root, int value) {
    if (root == nullptr) {
        return new Node{nullptr, nullptr, value, 1};
    }
    if (value < root->value) {
        root->left = Insert(root->left, value);
    } else if (value > root->value) {
        root->right = Insert(root->right, value);
    } else {
        return root;
    }
    root->height = GetMaxHeight(root);
    return Balance(root);
}

bool Find(Node *root, int value) {
    while (root) {
        if (value == root->value) {
            return true;
        } else if (value < root->value) {
            root = root->left;
        } else {
            root = root->right;
        }
    }
    return false;
}

Node *MaxNode(Node *root) {
    while (root->right) {
        root = root->right;
    }
    return root;
}

Node *Delete(Node *root, int value) {
    if (!root) return root;
    if (value < root->value) {
        root->left = Delete(root->left, value);
    } else if (value > root->value) {
        root->right = Delete(root->right, value);
    } else {
        if (root->left == nullptr || root->right == nullptr) {
            Node *node = root->left ? root->left : root->right;
            if (node == nullptr) {
                delete root;
                return nullptr;
            }
            *root = *node;
            delete node;
        } else {
            Node* node = MaxNode(root->left);
            root->value = node->value;
            root->left = Delete(root->left, node->value);
        }
    }
    root->height = GetMaxHeight(root);
    return Balance(root);
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int n;
    std::cin >> n;
    char symbol;
    int value;
    Node *head = nullptr;
    for (size_t i = 0; i < n; i++) {
        std::cin >> symbol >> value;
        if (symbol == 'A') {
            head = Insert(head, value);
            std::cout << GetBalance(head) << '\n';
        } else if (symbol == 'D') {
            head = Delete(head, value);
            std::cout << GetBalance(head) << '\n';
        } else {
            std::cout << (Find(head, value) ? 'Y' : 'N') << '\n';
        }
    }
}


