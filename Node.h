#include <iostream>
#include <vector>
using namespace std;


struct Node {
    string name;
    string id;
    int idInt;
    int height;
    Node* left;
    Node* right;

    Node(string name, string id);
    static int getHeight(Node* node);
    int getBalanceFactor();
};

