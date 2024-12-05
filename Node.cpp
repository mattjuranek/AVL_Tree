#include "Node.h"


Node::Node(string name, string id) {
    this->name = name;
    this->id = id;
    this->idInt = stoi(id);
    this->height = 0;
    this->left = nullptr;
    this->right = nullptr;
}

int Node::getHeight(Node* node) {
    if (node == nullptr) {
        return -1;
    }

    else {
        return node->height;
    }
}

int Node::getBalanceFactor() {
    int leftHeight = left ? left->height : -1;
    int rightHeight = right ? right->height : -1;
    return leftHeight - rightHeight;
}


