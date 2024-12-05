#include "Node.h"


class AVLTree {
private:
    Node* insertHelper(Node* node, string name, string idToInsert, bool& isInserted);
    Node* searchIDHelper(Node* node, string id);
    void searchNameHelper(Node* node, string name, vector<string>& matches);
    Node* removeHelper(Node* node, string idToRemove, bool& isRemoved);
    void printInorderHelper(Node* node, bool& isFirst);
    void printPreorderHelper(Node* node, bool& isFirst);
    void printPostorderHelper(Node* node, bool& isFirst);

public:
    Node* root;

    AVLTree();
    AVLTree(string name, string id);
    void updateHeight(Node* node);
    void insert(string name, string id);
    void searchID(string id);
    void searchName(string name);
    Node* rotateLeft(Node* node);
    Node* rotateRight(Node* node);
    Node* rotateLeftRight(Node* node);
    Node* rotateRightLeft(Node* node);
    void printInorder();
    void printPreorder();
    void printPostorder();
    void printLevelCount();
    void remove(string idToRemove);
    void removeInorder(int n);
    bool findInorder(Node* node, int& n, string& id);
};

