#include <iostream>
struct Node {
  int value = 0;
  Node *left = nullptr;
  Node *right = nullptr;
  int height = 1;
  int kid_l = 0;
  int kid_r = 0;
};

struct NodeQueue {
  NodeQueue *next = nullptr;
  Node *node = nullptr;
  Node *parent = nullptr;
};

Node *arr_child[200001] = {nullptr};

int GetHeight(Node *node) {
    return node ? node->height : 0;
}

int GetMaxHeight(Node *node) {
    return std::max(GetHeight(node->left), GetHeight(node->right)) + 1;
}

int UpdateMaxHeight(Node *node) {
    if (node == nullptr) return 0;
    node->height = std::max(UpdateMaxHeight(node->left), UpdateMaxHeight(node->right)) + 1;
    return node->height;
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
        return new Node{value};
    }
    if (value < root->value) {
        root->left = Insert(root->left, value);
    } else {
        root->right = Insert(root->right, value);
    }
    root->height = GetMaxHeight(root);
    return Balance(root);
}

void LevelOrderTraversal(Node *root, bool print = false) {
    int index = 1;
    auto *last_element = new NodeQueue{nullptr, root};
    NodeQueue *first_element = last_element;
    while (first_element != nullptr) {
        if (print) {
            std::cout << first_element->node->value << ' ' << first_element->node->kid_l << ' '
                      << first_element->node->kid_r << '\n';
        } else {
            if (first_element->parent && first_element->parent->left == first_element->node) {
                first_element->parent->kid_l = index;
            } else if (first_element->parent && first_element->parent->right == first_element->node) {
                first_element->parent->kid_r = index;
            }
        }
        if (first_element->node->left) {
            last_element->next = new NodeQueue{nullptr, first_element->node->left, first_element->node};
            last_element = last_element->next;
        }
        if (first_element->node->right) {
            last_element->next = new NodeQueue{nullptr, first_element->node->right, first_element->node};
            last_element = last_element->next;
        }
        first_element = first_element->next;
        index++;
    }
}

Node *AddNode(int K, int L, int R) {
    Node *node = new Node{K};
    arr_child[L] = node;
    arr_child[R] = node;
    return node;
}

int main() {
    int n;
    Node *head;
    std::cin >> n;
    std::cout << n + 1 << '\n';
    if (n == 0) {
        std::cin >> n;
        head = new Node{n};
        LevelOrderTraversal(head, true);
        return 0;
    }
    int K, L, R;
    std::cin >> K >> L >> R;
    head = AddNode(K, L, R);
    for (size_t i = 2; i <= n; i++) {
        std::cin >> K >> L >> R;
        if (K > arr_child[i]->value) {
            arr_child[i]->right = AddNode(K, L, R);
        } else {
            arr_child[i]->left = AddNode(K, L, R);
        }
    }
    UpdateMaxHeight(head);
    std::cin >> K;
    head = Insert(head, K);
    LevelOrderTraversal(head);
    LevelOrderTraversal(head, true);
}
