#include <iostream>
struct Node {
  Node *parent = nullptr;
  Node *left = nullptr;
  Node *right = nullptr;
  int value = 0;
  int delta = 0;
  int kid_l = 0;
  int kid_r = 0;
};

struct NodeQueue {
  NodeQueue *next = nullptr;
  Node *node = nullptr;
};

Node *arr_child[200001] = {nullptr};

int GetMaxHeight(Node *node) {
    if (node == nullptr) return 0;
    int l_height = GetMaxHeight(node->left);
    int r_height = GetMaxHeight(node->right);
    node->delta = r_height - l_height;
    return std::max(l_height, r_height) + 1;
}

Node *LeftRotate(Node *node) {
    Node *node_copy = node->right;
    node->right = node_copy->left;
    if (node->right) node->right->parent = node;

    node_copy->left = node;
    if (node_copy->left) node_copy->left->parent = node_copy;

    return node_copy;
}

Node *RightRotate(Node *node) {
    Node *node_copy = node->left;
    node->left = node_copy->right;
    if (node->left) node->left->parent = node;

    node_copy->right = node;
    if (node_copy->right) node_copy->right->parent = node_copy;

    return node_copy;
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
            if (first_element->node->parent && first_element->node->parent->left == first_element->node) {
                first_element->node->parent->kid_l = index;
            } else if (first_element->node->parent && first_element->node->parent->right == first_element->node) {
                first_element->node->parent->kid_r = index;
            }
        }
        if (first_element->node->left) {
            last_element->next = new NodeQueue{nullptr, first_element->node->left};
            last_element = last_element->next;

        }
        if (first_element->node->right) {
            last_element->next = new NodeQueue{nullptr, first_element->node->right};
            last_element = last_element->next;
        }
        first_element = first_element->next;
        index++;
    }
}

Node *AddNode(int K, int L, int R) {
    Node *node = new Node{nullptr, nullptr, nullptr, K};
    arr_child[L] = node;
    arr_child[R] = node;
    return node;
}

int main() {
    int n;
    int K, L, R;
    std::cin >> n;
    std::cin >> K >> L >> R;
    Node *head = AddNode(K, L, R);
    for (size_t i = 2; i <= n; i++) {
        std::cin >> K >> L >> R;
        if (K > arr_child[i]->value) {
            arr_child[i]->right = AddNode(K, L, R);
            arr_child[i]->right->parent = arr_child[i];
        } else {
            arr_child[i]->left = AddNode(K, L, R);
            arr_child[i]->left->parent = arr_child[i];
        }
    }
    GetMaxHeight(head);
    if (head->delta == 2) {
        if (head->right->delta == -1) {
            head->right = RightRotate(head->right);
        }
        head = LeftRotate(head);
    }
    std::cout << n << '\n';
    LevelOrderTraversal(head);
    LevelOrderTraversal(head, true);
}
