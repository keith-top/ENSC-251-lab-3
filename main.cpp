#include <iostream>
#include <limits>
#include "BinarySearchTree.hpp"

using namespace std;
using namespace lab3;

void printNodeDetails(NodePtr n) {
    if (!n) {
        cout << "Node: NULL\n";
        return;
    }
    cout << "Node key: " << n->key << endl;
    if (n->parent) cout << " Parent: " << n->parent->key << endl;
    else cout << " Parent: NULL" << endl;
    if (n->left) cout << " Left child: " << n->left->key << endl;
    else cout << " Left child: NULL" << endl;
    if (n->right) cout << " Right child: " << n->right->key << endl;
    else cout << " Right child: NULL" << endl;
}

int getIntFromUser(const string& prompt) {
    int x;
    while (true) {
        cout << prompt;
        if (cin >> x) return x;
        cout << "Invalid input. Please enter an integer" << endl;
        cin.clear();
    }
}

int main() {
    // Part 1: automated tests
    BinarySearchTree bst1;
    int keysArr[] = {10, 5, 15, 3, 7, 13, 18, 4, 6, 9, 8, 16, 19, 17};
    cout << "Inserting into bst1 and printing after each insertion:" << endl;
    for (int k : keysArr) {
        bst1.insertNode(k);
        cout << "After inserting " << k << ":\n" << bst1 << endl;
    }

    // Second: assignment and copies
    BinarySearchTree bst2, bst3;
    bst2 = bst1;
    bst3 = bst2;
    cout << "bst2 (after assignment bst2 = bst1):\n" << bst2 << endl;
    cout << "bst3 (after assignment bst3 = bst2):\n" << bst3 << endl;

    // copy constructor
    BinarySearchTree bst4(bst3);
    cout << "bst4 (copy constructed from bst3):\n" << bst4 << endl;

    // Deletions per instructions
    cout << "Deleting nodes 4 and 9 from bst1:" << endl;
    bst1.deleteNode(4);
    cout << "bst1 after deleting 4:\n" << bst1 << endl;
    bst1.deleteNode(9);
    cout << "bst1 after deleting 9:\n" << bst1 << endl;

    cout << "Deleting node 10 from bst2:\n";
    bst2.deleteNode(10);
    cout << "bst2 after deleting 10:\n" << bst2 << endl;

    cout << "Deleting nodes 3, 9, and 16 from bst3:" << endl;
    bst3.deleteNode(3);
    cout << "bst3 after deleting 3:\n" << bst3 << endl;
    bst3.deleteNode(9);
    cout << "bst3 after deleting 9:\n" << bst3 << endl;
    bst3.deleteNode(16);
    cout << "bst3 after deleting 16:\n" << bst3 << endl;

    cout << "Deleting nodes 18, 7, and 10 from bst4:" << endl;
    bst4.deleteNode(18);
    cout << "bst4 after deleting 18:\n" << bst4 << endl;
    bst4.deleteNode(7);
    cout << "bst4 after deleting 7:\n" << bst4 << endl;
    bst4.deleteNode(10);
    cout << "bst4 after deleting 10:\n" << bst4 << endl;

    cout << "Final print of bst1, bst2, bst3, bst4:" << endl;
    cout << "bst1:\n" << bst1 << endl;
    cout << "bst2:\n" << bst2 << endl;
    cout << "bst3:\n" << bst3 << endl;
    cout << "bst4:\n" << bst4 << endl;

    // Part 2: interactive menu for bst4
    cout << "=== Interactive session for bst4 ===" << endl;
    bool keepRunning = true;
    while (keepRunning) {
        cout << endl << "Menu:" << endl
             << "1) Search a key in bst4" << endl
             << "2) Search the successor of a key in bst4" << endl
             << "3) Insert a key into bst4" << endl
             << "4) Delete a key from bst4" << endl
             << "5) Print bst4" << endl
             << "6) Exit" << endl
             << "Enter choice (1-6): ";
        int choice;
        if (!(cin >> choice)) {
            cout << "Invalid input. Exiting interactive session." << endl;
            break;
        }
        switch (choice) {
            case 1: {
                int k = getIntFromUser("Enter key to search: ");
                NodePtr n = bst4.searchNode(k);
                if (n) printNodeDetails(n);
                else cout << "Key " << k << " not found in bst4." << endl;
                break;
            }
            case 2: {
                int k = getIntFromUser("Enter key to find successor: ");
                NodePtr s = bst4.searchSuccessor(k);
                if (s) printNodeDetails(s);
                else cout << "No successor (or key not found) for key. " << k << endl;
                break;
            }
            case 3: {
                int k = getIntFromUser("Enter key to insert: ");
                if (bst4.insertNode(k)) cout << "Inserted " << k << " into bst4." << endl;
                else cout << "Insert failed for key " << k << endl;
                break;
            }
            case 4: {
                int k = getIntFromUser("Enter key to delete: ");
                if (bst4.deleteNode(k)) cout << "Deleted " << k << " from bst4 (if existed)." << endl;
                else cout << "Delete failed for key " << k << endl;
                break;
            }
            case 5:
                cout << "bst4:" << endl << bst4 << endl;
                break;
            case 6:
                keepRunning = false;
                break;
            default:
                cout << "Invalid choice." << endl;
        }
    }

    cout << "Exiting program." << endl;
    return 0;
}
