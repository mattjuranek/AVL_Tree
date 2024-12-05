#include "AVLTree.h"


AVLTree::AVLTree() {
    root = nullptr;
}

AVLTree::AVLTree(string name, string id) {
    this->root = new Node(name, id);
}

void AVLTree::updateHeight(Node* node) {
    if (node != nullptr) {
        int leftHeight = Node::getHeight(node->left);
        int rightHeight = Node::getHeight(node->right);
        node->height = max(leftHeight, rightHeight) + 1;
    }
}

Node* AVLTree::insertHelper(Node* node, string name, string idToInsert, bool& isInserted) {
    int idToInsertInt = stoi(idToInsert);

    if (node == nullptr) {
        isInserted = true;
        return new Node(name, idToInsert);
    }

        // Check left subtree
    else if (idToInsertInt < node->idInt) {
        node->left = insertHelper(node->left, name, idToInsert, isInserted);
    }

        // Check right subtree
    else if (idToInsertInt > node->idInt) {
        node->right = insertHelper(node->right, name, idToInsert, isInserted);
    }

    else {
        isInserted = false;
        return node;
    }

    // Update height
    updateHeight(node);
    int balanceFactor = node->getBalanceFactor();

    // Left-Left -> rotate right
    if (balanceFactor > 1 && idToInsertInt < node->left->idInt) {
        return rotateRight(node);
    }

    // Right-Right -> rotate left
    if (balanceFactor < -1 && idToInsertInt > node->right->idInt) {
        return rotateLeft(node);
    }

    // Left-Right -> rotate left-right
    if (balanceFactor > 1 && idToInsertInt > node->left->idInt) {
        return rotateLeftRight(node);
    }

    // Right-Left -> rotate right-left
    if (balanceFactor < -1 && idToInsertInt < node->right->idInt) {
        return rotateRightLeft(node);
    }

    return node;
}

void AVLTree::insert(string name, string id) {
    bool isInserted = false;

    try {
        this->root = insertHelper(this->root, name, id, isInserted);
    }
    catch (exception &err) {
        return;
    }

    if (isInserted) {
        cout << "successful" << endl;
    }

    else {
        cout << "unsuccessful" << endl;
    }
}

Node* AVLTree::searchIDHelper(Node* node, string id) {
    int idInt = stoi(id);

    if (node == nullptr) {
        return nullptr;
    }

    else if (node->idInt == idInt) {
        return node;
    }

    else if (idInt < node->idInt) {
        return searchIDHelper(node->left, id);
    }

    else {
        return searchIDHelper(node->right, id);
    }
}

void AVLTree::searchID(string id) {
    Node* result = searchIDHelper(this->root, id);

    // If ID found, print out name
    if (result != nullptr) {
        cout << result->name << endl;
    }

    else {
        cout << "unsuccessful" << endl;
    }
}

void AVLTree::searchNameHelper(Node *node, string name, vector<string>& matches) {
    if (node == nullptr) {
        return;
    }

    // If name matches, push ID to vector
    if (node->name == name) {
        matches.push_back(node->id);
    }

    // Search left and right subtrees
    searchNameHelper(node->left, name, matches);
    searchNameHelper(node->right, name, matches);
}

void AVLTree::searchName(string name) {
    vector<string> matches;
    searchNameHelper(this->root, name, matches);

    // If match is found
    if (!matches.empty()) {
        for (string id : matches) {
            cout << id << endl;
        }
    }

        // If no matches found
    else {
        cout << "unsuccessful" << endl;
    }
}

Node* AVLTree::rotateLeft(Node *node) {
    Node* newRoot = node->right;
    Node* subtree = newRoot->left;

    newRoot->left = node;
    node->right = subtree;

    // Update height
    updateHeight(node);
    updateHeight(newRoot);

    return newRoot;
}

Node* AVLTree::rotateRight(Node *node) {
    Node* newRoot = node->left;
    Node* subtree = newRoot->right;

    newRoot->right = node;
    node->left = subtree;

    // Update height
    updateHeight(node);
    updateHeight(newRoot);

    return newRoot;
}

Node* AVLTree::rotateLeftRight(Node *node) {
    node->left = rotateLeft(node->left);
    return rotateRight(node);
}

Node* AVLTree::rotateRightLeft(Node* node) {
    node->right = rotateRight(node->right);
    return rotateLeft(node);
}

// LNR
void AVLTree::printInorderHelper(Node* node, bool& isFirst) {
    if (node == nullptr) {
        return;
    }

    printInorderHelper(node->left, isFirst);

    if (!isFirst) {
        cout << ", ";
    }

    cout << node->name;

    isFirst = false;
    printInorderHelper(node->right, isFirst);
}

// NLR
void AVLTree::printPreorderHelper(Node* node, bool& isFirst) {
    if (node == nullptr) {
        return;
    }

    if (!isFirst) {
        cout << ", ";
    }

    cout << node->name;

    isFirst = false;
    printPreorderHelper(node->left, isFirst);
    printPreorderHelper(node->right, isFirst);

}

// LRN
void AVLTree::printPostorderHelper(Node* node, bool& isFirst){
    if (node == nullptr) {
        return;
    }

    printPostorderHelper(node->left, isFirst);
    printPostorderHelper(node->right, isFirst);

    if (!isFirst) {
        cout << ", ";
    }

    cout << node->name;

    isFirst = false;
}

void AVLTree::printInorder() {
    bool isFirst = true;
    printInorderHelper(this->root, isFirst);
    cout << endl;
}

void AVLTree::printPreorder() {
    bool isFirst = true;
    printPreorderHelper(this->root, isFirst);
    cout << endl;
}

void AVLTree::printPostorder() {
    bool isFirst = true;
    printPostorderHelper(this->root, isFirst);
    cout << endl;
}

Node* AVLTree::removeHelper(Node* node, string idToRemove, bool& isRemoved) {
    int idToRemoveInt = stoi(idToRemove);

    if (node == nullptr) {
        return node;
    }

    // If ID is less than current node's ID, check left subtree
    if (idToRemoveInt < node->idInt) {
        node->left = removeHelper(node->left, idToRemove, isRemoved);
    }

        // If ID is greater than current node's ID, check right subtree
    else if (idToRemoveInt > node->idInt) {
        node->right = removeHelper(node->right, idToRemove, isRemoved);
    }

        // When ID is found
    else if (idToRemoveInt == node->idInt) {
        // If one or no children
        if (node->left == nullptr || node->right == nullptr) {
            Node *temp = node->left ? node->left : node->right;

            // If no children
            if (temp == nullptr) {
                delete node;
                node = nullptr;
            }

                // If one child
            else {
                Node *toDelete = node;
                node = temp;
                delete toDelete;
            }

            isRemoved = true;
        }

            // If two children
        else {
            // Find inorder successor (smallest in right subtree) and parent
            Node *successorParent = node;
            Node *successor = node->right;

            while (successor->left != nullptr) {
                successorParent = successor;
                successor = successor->left;
            }

            // If  successor is direct right child
            if (successor != node->right) {
                successorParent->left = successor->right;
            }

            node->id = successor->id;
            node->idInt = successor->idInt;
            node->name = successor->name;

            // If successor is not direct right child
            if (successor != node->right) {
                delete successor;
            }

            else {
                // If successor is direct right child
                node->right = removeHelper(node->right, successor->id, isRemoved);
            }

            isRemoved = true;
        }
    }

    if (node == nullptr) {
        return node;
    }

    // Update height
    updateHeight(root);

    return node;
}

void AVLTree::remove(string idToRemove) {
    bool isRemoved = false;
    root = removeHelper(root, idToRemove, isRemoved);

    if (isRemoved) {
        cout << "successful" << endl;
    }

    else {
        cout << "unsuccessful" << endl;
    }
}

void AVLTree::printLevelCount() {
    cout << Node::getHeight(root) + 1 << endl;
}

bool AVLTree::findInorder(Node *node, int& n, string& id) {
    if (node == nullptr) {
        return false;
    }

    // Search left subtree (L)
    bool inLeft = findInorder(node->left, n, id);

    // If found in left subtree
    if (inLeft) {
        return true;
    }

    // Search current node (N)
    if (n == 0) {
        id = node->id;
        return true;
    }
    n--;

    // Search right subtree (R)
    bool inRight = findInorder(node->right, n , id);

    // If found in right subtree
    if (inRight) {
        return true;
    }

    return false;
}

void AVLTree::removeInorder(int n) {
    string idToRemove = "";
    bool isRemoved;

    bool isFound = findInorder(this->root, n, idToRemove);

    if (isFound && idToRemove != "") {
        isRemoved = false;
        root = removeHelper(root, idToRemove, isRemoved);

        if (isRemoved) {
            cout << "successful" << endl;
        }

        else {
            cout << "unsuccessful" << endl;
        }
    }

        // If Nth node not found
    else {
        cout << "unsuccessful" << endl;
    }
}