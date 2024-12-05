#include "AVLTree.h"
#include <sstream>


/* Note:
	1. You will have to comment main() when unit testing your code because catch uses its own main().
	2. You will submit this main.cpp file and any header files you have on Gradescope.
*/

bool isValidID(string& id) {
    // Only valid if ID is 8 numerical digits
    if (id.length() != 8) {
        return false;
    }

    for (char c : id) {
        if (!isdigit(c)) {
            return false;
        }
    }

    return true;
}

bool isValidName(string& name) {
    // Only valid if character is alphabetical or whitespace
    if (name.front() != '"' || name.back() != '"') {
        return false;
    }

    for (int i = 1; i < name.size() - 1; i++) {
        char c = name[i];

        if (!isalpha(c) && c != ' ') {
            return false;
        }
    }

    return true;
}


int main() {
    AVLTree tree;

    // Read line to determine number of input lines read
    int numLines;
    cin >> numLines;

    string firstLine;
    getline(cin, firstLine);

    // Loop for N amount of lines before terminating
    while (numLines > 0) {
        string line;
        getline(cin, line);

        stringstream ss(line);
        string command, arg1, arg2;

        // Read the command
        ss >> command;

        if (command == "insert") {
            // Ignore whitespace after command
            ss >> ws;

            // Read arg1 and arg2
            ss >> arg1;
            ss >> arg2;

            if (!isValidName(arg1) || !isValidID(arg2)) {
                cout << "unsuccessful" << endl;
            }

            else {
                string name = arg1;
                string id = arg2;

                name.pop_back();
                name.erase(0,1);
                tree.insert(name, id);
            }
        }

        else if (command == "remove") {
            ss >> arg1;

            if (!isValidID(arg1)) {
                cout << "unsuccessful" << endl;
            }

            else {
                string id = arg1;
                tree.remove(id);
            }
        }

        // search ID, search NAME
        else if (command == "search") {
            // Read arg1
            ss >> arg1;

            if (isValidID(arg1)) {
                tree.searchID(arg1);
            }

            else if (isValidName(arg1)) {
                string name = arg1;
                name.pop_back();
                name.erase(0, 1);

                tree.searchName(name);
            }

            else {
                cout << "unsuccessful" << endl;
            }
        }

        // printInorder
        else if (command == "printInorder") {
            tree.printInorder();
        }

        // printPreorder
        else if (command == "printPreorder") {
            tree.printPreorder();
        }

        // printPostorder
        else if (command == "printPostorder") {
            tree.printPostorder();
        }

        // printLevelCount
        else if (command == "printLevelCount") {
            tree.printLevelCount();
        }

        // removeInorder N
        else if (command == "removeInorder") {
            // Read arg1
            ss >> arg1;

            try {
                int n = stoi(arg1);
                tree.removeInorder(n);
            }

            catch (exception &err) {
                cout << "unsuccessful" << endl;
            }
        }

        // If command is not valid
        else {
            cout << "unsuccessful" << endl;
        }

        numLines--;
    }

    return 0;
}