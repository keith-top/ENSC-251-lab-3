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
    cout << "Node key: " << n->key << "\n";
    if (n->parent) cout << " Parent: " << n->parent->key << "\n";
    else cout << " Parent: NULL\n";
    if (n->left) cout << " Left child: " << n->left->key << "\n";
    else cout << " Left child: NULL\n";
    if (n->right) cout << " Right child: " << n->right->key << "\n";
    else cout << " Right child: NULL\n";
}

int getIntFromUser(const string& prompt) {
    int x;
    while (true) {
        cout << prompt;
        if (cin >> x) return x;
        cout << "Invalid input. Please enter an integer.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int main() {
    // Part 1: automated tests
    BinarySearchTree bst1;
    int keysArr[] = {10, 5, 15, 3, 7, 13, 18, 4, 6, 9, 8, 16, 19, 17};
    cout << "Inserting into bst1 and printing after each insertion:\n";
    for (int k : keysArr) {
        bst1.insertNode(k);
        cout << "After inserting " << k << ":\n" << bst1 << "\n";
    }

    // Second: assignment and copies
    BinarySearchTree bst2, bst3;
    bst2 = bst1;
    bst3 = bst2;
    cout << "bst2 (after assignment bst2 = bst1):\n" << bst2 << "\n";
    cout << "bst3 (after assignment bst3 = bst2):\n" << bst3 << "\n";

    // copy constructor
    BinarySearchTree bst4(bst3);
    cout << "bst4 (copy constructed from bst3):\n" << bst4 << "\n";

    // Deletions per instructions
    cout << "Deleting nodes 4 and 9 from bst1:\n";
    bst1.deleteNode(4);
    cout << "bst1 after deleting 4:\n" << bst1 << "\n";
    bst1.deleteNode(9);
    cout << "bst1 after deleting 9:\n" << bst1 << "\n";

    cout << "Deleting node 10 from bst2:\n";
    bst2.deleteNode(10);
    cout << "bst2 after deleting 10:\n" << bst2 << "\n";

    cout << "Deleting nodes 3, 9, and 16 from bst3:\n";
    bst3.deleteNode(3);
    cout << "bst3 after deleting 3:\n" << bst3 << "\n";
    bst3.deleteNode(9);
    cout << "bst3 after deleting 9:\n" << bst3 << "\n";
    bst3.deleteNode(16);
    cout << "bst3 after deleting 16:\n" << bst3 << "\n";

    cout << "Deleting nodes 18, 7, and 10 from bst4:\n";
    bst4.deleteNode(18);
    cout << "bst4 after deleting 18:\n" << bst4 << "\n";
    bst4.deleteNode(7);
    cout << "bst4 after deleting 7:\n" << bst4 << "\n";
    bst4.deleteNode(10);
    cout << "bst4 after deleting 10:\n" << bst4 << "\n";

    cout << "Final print of bst1, bst2, bst3, bst4:\n";
    cout << "bst1:\n" << bst1 << "\n";
    cout << "bst2:\n" << bst2 << "\n";
    cout << "bst3:\n" << bst3 << "\n";
    cout << "bst4:\n" << bst4 << "\n";

    // Part 2: interactive menu for bst4
    cout << "=== Interactive session for bst4 ===\n";
    bool keepRunning = true;
    while (keepRunning) {
        cout << "\nMenu:\n"
             << "1) Search a key in bst4\n"
             << "2) Search the successor of a key in bst4\n"
             << "3) Insert a key into bst4\n"
             << "4) Delete a key from bst4\n"
             << "5) Print bst4\n"
             << "6) Exit\n"
             << "Enter choice (1-6): ";
        int choice;
        if (!(cin >> choice)) {
            cout << "Invalid input. Exiting interactive session.\n";
            break;
        }
        switch (choice) {
            case 1: {
                int k = getIntFromUser("Enter key to search: ");
                NodePtr n = bst4.searchNode(k);
                if (n) printNodeDetails(n);
                else cout << "Key " << k << " not found in bst4.\n";
                break;
            }
            case 2: {
                int k = getIntFromUser("Enter key to find successor: ");
                NodePtr s = bst4.searchSuccessor(k);
                if (s) printNodeDetails(s);
                else cout << "No successor (or key not found) for key " << k << ".\n";
                break;
            }
            case 3: {
                int k = getIntFromUser("Enter key to insert: ");
                if (bst4.insertNode(k)) cout << "Inserted " << k << " into bst4.\n";
                else cout << "Insert failed for key " << k << ".\n";
                break;
            }
            case 4: {
                int k = getIntFromUser("Enter key to delete: ");
                if (bst4.deleteNode(k)) cout << "Deleted " << k << " from bst4 (if existed).\n";
                else cout << "Delete failed for key " << k << ".\n";
                break;
            }
            case 5:
                cout << "bst4:\n" << bst4 << "\n";
                break;
            case 6:
                keepRunning = false;
                break;
            default:
                cout << "Invalid choice.\n";
        }
    }

    cout << "Exiting program.\n";
    return 0;
}
