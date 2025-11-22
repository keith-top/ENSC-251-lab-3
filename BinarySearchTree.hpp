#ifndef BinarySearchTree_hpp
#define BinarySearchTree_hpp
#include <iostream>

namespace lab3{

struct Node{
    int key;
    Node* parent;
    Node* left;
    Node* right;
    Node(int k) : key(k), parent(nullptr), left(nullptr), right(nullptr) {}
};

typedef Node* NodePtr;

class BinarySearchTree {
private:
    NodePtr root;
    
    void copyTree(NodePtr& thisNode, NodePtr otherNode, NodePtr parentNode); //copy constructor
    void deleteTree(NodePtr& node); //deconstructor
    NodePtr searchNodeHelper(NodePtr node, int key) const;
    NodePtr searchSuccessorHelper(NodePtr node) const;

public:
    BinarySearchTree(); //initializes root to nullptr
    BinarySearchTree(const BinarySearchTree&); //copy constructor
    ~BinarySearchTree(); //deconstructor
    
    BinarySearchTree& operator=(const BinarySearchTree&); //assignment operator

    bool insertNode(int key); //inserts node 'key', true is successful
    bool deleteNode(int key); //removes knode 'key', true is successful
    NodePtr searchNode(int key) const; //searches for node with key, returns pointer to node otherwise nullptr
    NodePtr searchSuccessor(int key) const; //if key is not in BST or is the largest, print warning and return null.
    //otherwise, if key is in the BST, return successor node whose key is the smallest nuber that is bigger than input key
   
    NodePtr getRoot() const;

    friend std::ostream& operator<<(std::ostream& os, const BinarySearchTree& tree);
};
}
#endif