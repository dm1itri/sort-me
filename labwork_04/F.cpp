#include <iostream>
# define min(a, b) a < b ? a : b
# define max(a, b) a > b ? a : b
struct Node {
  Node *parent = nullptr;
  Node *left = nullptr;
  Node *right = nullptr;
  long long value = 0;
};
struct CheckBST {
  bool BST = false;
  long long max_sum = 0;
  long long left = INT64_MAX;
  long long right = INT64_MIN;
};

long long max_sum_value = 0;

CheckBST MaxSum(Node *root) {
    if (root == nullptr) {
        return CheckBST{true};;
    }
    if (root->left == nullptr && root->right == nullptr) {
        if (root->value > max_sum_value) max_sum_value = root->value;
        return CheckBST{true, root->value, root->value, root->value};
    }
    CheckBST l_tree = MaxSum(root->left);
    CheckBST r_tree = MaxSum(root->right);
    if (l_tree.BST && r_tree.BST && l_tree.right < root->value && root->value < r_tree.left) {
        CheckBST check_bst = CheckBST{true, l_tree.max_sum + r_tree.max_sum + root->value};
        check_bst.left = min(l_tree.left, root->value);
        check_bst.right = max(r_tree.right, root->value);
        if (check_bst.max_sum > max_sum_value) max_sum_value = check_bst.max_sum;
        return check_bst;
    }
    return CheckBST{};
}

int main() {
    Node *head = new Node;
    Node *node = head;
    char symbol[100];
    std::cin >> head->value;
    while (node != nullptr) {
        std::cin >> symbol;
        if (symbol[0] == 'l') {
            if (node->left == nullptr) {
                Node *new_node = new Node;
                new_node->parent = node;
                node->left = new_node;
            }
            node = node->left;
        } else if (symbol[0] == 'r') {
            if (node->right == nullptr) {
                Node *new_node = new Node;
                new_node->parent = node;
                node->right = new_node;
            }
            node = node->right;
        } else if (symbol[0] == 'u') {
            node = node->parent;
        } else {

            node->value = 0;
            for (uint8_t i = symbol[0] == '-'; symbol[i] != '\0'; i++) {
                node->value *= 10;
                node->value += symbol[i] - '0';
                symbol[i] = '\0';
            }
            if (symbol[0] == '-') node->value *= -1;
        }
    }
    MaxSum(head);
    std::cout << max_sum_value;
}

