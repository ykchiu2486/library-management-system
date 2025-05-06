#pragma once
#include "Book.h"
#include "Heap.h"
#include "Similarity.h"
#include <iostream>
using namespace std;

class BookDB {
private:
    enum Color { RED, BLACK };

    struct Node {
        Book* data;
        Color color;
        Node *left, *right, *parent;
        Node(Book* b)
            : data(b), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
    };
    Node* root;
    long long int bookNumbers = 0;
    void leftRotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        if (y->left) y->left->parent = x;
        y->parent = x->parent;
        if (!x->parent) root = y;
        else if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    void rightRotate(Node* y) {
        Node* x = y->left;
        y->left = x->right;
        if (x->right) x->right->parent = y;
        x->parent = y->parent;
        if (!y->parent) root = x;
        else if (y == y->parent->left) y->parent->left = x;
        else y->parent->right = x;
        x->right = y;
        y->parent = x;
    }

    void fixInsert(Node* z) {
        while (z->parent && z->parent->color == RED) {
            Node* gp = z->parent->parent;
            if (!gp) break;
            if (z->parent == gp->left) {
                Node* uncle = gp->right;
                // Case 1: Uncle is red, recolor it
                if (uncle && uncle->color == RED) {
                    z->parent->color = BLACK;
                    uncle->color = BLACK;
                    gp->color = RED;
                    z = gp;
                } 
                else {
                    // Case 2: z at right, leftRotation() -> Case 3
                    if (z == z->parent->right) {
                        z = z->parent;
                        leftRotate(z);
                    }
                    // Case 3: z at left, RightRotate
                    z->parent->color = BLACK;
                    gp->color = RED;
                    rightRotate(gp);
                }
            } else {
                // mirror case: at right
                Node* uncle = gp->left;
                if (uncle && uncle->color == RED) {
                    z->parent->color = BLACK;
                    uncle->color = BLACK;
                    gp->color = RED;
                    z = gp;
                } 
                else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        rightRotate(z);
                    }
                    z->parent->color = BLACK;
                    gp->color = RED;
                    leftRotate(gp);
                }
            }
        }
        root->color = BLACK;  //root should be black
    }

    void deleteTree(Node* node) {
        if (!node) return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }

    void inorderPrint(Node* node) const {
        if (node == nullptr) return;
        inorderPrint(node->left);
        node->data->displayBookInfo();
        cout << endl;
        inorderPrint(node->right);
    }


    void postorderHeap(Node* node, Heap& heap, string s) {\
        if(node == nullptr) return;
        postorderHeap(node->left, heap, s);
        postorderHeap(node->right, heap, s);
        auto& book = node->data;
        book->setSimilarity(similarity(book->getTitle(), s));
        heap.insert(book);
    }

public:
    BookDB() : root(nullptr) {}
    ~BookDB() {
        deleteTree(root);
    }

    bool addBook(Book* b) {
        Node* z = new Node(b);
        Node* y = nullptr;
        Node* x = root;
        while (x) {
            y = x;
            if (*(z->data) < *(x->data))
                x = x->left;
            else if (*(x->data) < *(z->data))
                x = x->right;
            else {
                // if the same, delete
                delete z;
                return false;
            }
        }
        z->parent = y;
        if (!y) root = z;
        else if (*(z->data) < *(y->data)) y->left = z;  
        else y->right = z;
    
        fixInsert(z);
        bookNumbers += 1;
        return true;
    }

    void printTree() const { inorderPrint(root); }

    int getbookNumbers() { return bookNumbers; }

    vector<Book*> searchSimilarity(string s, int n) {
        Heap heap;
        postorderHeap(root, heap, s);
        vector<Book*> ans;
        
        for(int i = 0; i < n; i++) {
            ans.push_back(heap.pop());
        }
        return ans;
    }
};
