#include <iostream>

struct Node {
  Node *left = nullptr;
  Node *right = nullptr;
  char value[100];
  int height = 1;
  bool first = false;
  bool second = false;
  bool third = false;
};

int countPoints[3] = {0};

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

Node *Insert(Node *root, const char *value, int child) {
    if (root == nullptr) {
        Node *node = new Node;
        strcpy(node->value, value);
        node->first = child == 0;
        node->second = child == 1;
        node->third = child == 2;
        return node;
    }
    if (strcmp(value, root->value) < 0) {
        root->left = Insert(root->left, value, child);
    } else if (strcmp(value, root->value) > 0) {
        root->right = Insert(root->right, value, child);
    } else {
        if (child == 1) root->second = true;
        if (child == 2) root->third = true;
        return root;
    }
    root->height = GetMaxHeight(root);
    return Balance(root);
}

void UpdateCount(Node *root) {
    if (!root) return;
    if (root->first && root->second && root->third) {
    } else if (root->first && root->second) {
        countPoints[0] += 1;
        countPoints[1] += 1;
    } else if (root->first && root->third) {
        countPoints[0] += 1;
        countPoints[2] += 1;
    } else if (root->second && root->third) {
        countPoints[1] += 1;
        countPoints[2] += 1;
    } else if (root->first) {
        countPoints[0] += 3;
    } else if (root->second) {
        countPoints[1] += 3;
    } else {
        countPoints[2] += 3;
    }
    UpdateCount(root->left);
    UpdateCount(root->right);
}

int main() {
    int n;
    std::cin >> n;
    char symbols[100];
    Node *head = nullptr;
    for (int j = 0; j < 3; j++) {
        for (size_t i = 0; i < n; i++) {
            std::cin >> symbols;
            head = Insert(head, symbols, j);
        }
    }
    UpdateCount(head);
    std::cout << countPoints[0] << ' ' << countPoints[1] << ' ' << countPoints[2];
}
