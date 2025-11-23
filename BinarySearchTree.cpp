#include "BinarySearchTree.hpp"
#include <iostream>
using namespace lab3;
using namespace std;

//recursively copies tree
void BinarySearchTree::copyTree(NodePtr& thisNode, NodePtr otherNode, NodePtr parentNode) {
    if (otherNode == nullptr) {
        thisNode = nullptr;
        return;
    }
    thisNode = new Node(otherNode->key);
    thisNode->parent = parentNode;
    copyTree(thisNode->left, otherNode->left, thisNode);
    copyTree(thisNode->right, otherNode->right, thisNode);
}

//recursively deletes tree
void BinarySearchTree::deleteTree(NodePtr& node) {
    if (node != nullptr) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
        node = nullptr;
    }
}

//helper function for searchNode, recursively searches for node with key, returns node with requested key
NodePtr BinarySearchTree::searchNodeHelper(NodePtr node, int key) const {
    if (node == nullptr || node->key == key) {
        return node;
    }
    if (key < node->key){
        return searchNodeHelper(node->left, key);
    }
    return searchNodeHelper(node->right, key);

}

//helper function for searchSuccessor, goes once to right child, then goes to leftmost child
NodePtr BinarySearchTree::searchSuccessorHelper(NodePtr node) const {
    NodePtr current = node->right;
    while (current != nullptr && current->left != nullptr) {
        current = current->left;
    }
    return current;
}

//initializes root to nullptr
BinarySearchTree::BinarySearchTree() : root(nullptr) {}

//copy constructor
BinarySearchTree::BinarySearchTree(const BinarySearchTree& other) : root(nullptr) {
    copyTree(root, other.root, nullptr);
}

//deconstructor
BinarySearchTree::~BinarySearchTree() {
    deleteTree(root);
}

//assignment operator
BinarySearchTree& BinarySearchTree::operator=(const BinarySearchTree& other) {
    if (this != &other) {
        deleteTree(root);
        copyTree(this->root, other.root, nullptr);
    }
    return *this;
}

//returns the root of the tree
NodePtr BinarySearchTree::getRoot() const {
    return root;
}

//inserts node with key and propery parent/child relationships. Returns true if successful, false if key already exists
bool BinarySearchTree::insertNode(int key){
    if(root == nullptr){ //if there is no root, create one
        root = new Node(key);
        return true;
    }
    NodePtr curr = root;
    NodePtr parent = nullptr;
    //move curr down the tree to find insertion point
    while(curr != nullptr){//while loop ends when curr is nullptr, and parent is the parent of the node to be inserted
        parent = curr; //set parent to curr before moving curr down the tree
        if(key < curr->key){
            curr = curr->left;
        }
        else if(key > curr->key){
            curr = curr->right;
        }
        else{ //if key already exists
            return false;
        }
    }
    NodePtr newNode = new Node(key);
    newNode->parent = parent;
    if(key < parent->key){ //insert as left child
        parent->left = newNode;
    }
    else{ //insert as right child
        parent->right = newNode;
    }
    return true;
}

//deletes a node and remaps the tree accordingly. Returns true if successful, false if key not found
bool BinarySearchTree::deleteNode(int key){
    NodePtr node = searchNodeHelper(root, key); //find node to delete
    if (node == nullptr){
        cout << "Key " << key << " not found in the tree." << endl;
         return false; //key not found
    }
    NodePtr parent = node->parent;

    //node has 1 or no children
    if(node->left == nullptr || node->right == nullptr){
        NodePtr child;
        if(node->left != nullptr){ //if node has left child
            child = node->left;
        }
        else if(node->right != nullptr){ //if node has right child
            child = node->right;
        }
        else{ //node has no children
            child = nullptr;
        }

        if(parent == nullptr){
            root = child; //deleting root node
        }
        else if(parent->left == node){ //node is left child
            parent->left = child;
        }
        else{ //node is right child
            parent->right = child;
        }
        if(child != nullptr){ //update child's parent pointer
            child->parent = parent;
        }
        delete node;
    }

    //node has 2 children
    else{
        NodePtr successor = searchSuccessorHelper(node); //find successor and use recursion
        int succKey = successor->key;
        deleteNode(succKey); //delete successor node
        node->key = succKey; //replace node's key with successor's key
    }
    return true;
}

NodePtr BinarySearchTree::searchNode(int key) const{
    return searchNodeHelper(root, key);
}

//searches for node with lowest value higher than key
NodePtr BinarySearchTree::searchSuccessor(int key) const{
    NodePtr curr = searchNodeHelper(root, key);
    if (curr == nullptr){
        cout << "Key " << key << " not found in the tree." << endl;
        return nullptr; //key not found
    } 
    if (curr->right != nullptr){
        return searchSuccessorHelper(curr);
    }
    NodePtr parent = curr->parent;
    while(parent != nullptr && curr == parent->right){
        curr = parent;
        parent = parent->parent;
    }
    if(parent == nullptr){
        cout << "Error: " << key << "is not in the current BST or the largest in the current BST" << endl;
        cout << "Key " << key << " is the root" << endl;
        return nullptr; //no successor
    }
    return parent;
}

void printInOrder(ostream& os, NodePtr node){
    if(node != nullptr){
        printInOrder(os, node->left);
        os << node->key << " ";
        printInOrder(os, node->right);
    }
}

ostream& lab3::operator<<(ostream& os, const BinarySearchTree& tree){
    printInOrder(os, tree.root);
    return os;
}
