#pragma once
#include "Book.h"
#include "Heap.h"
#include "Similarity.h"
#include "Show.h"
#include <fstream>
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
        delete node->data;
        delete node;
    }

    // void inorderPrint(Node* node) const {
    //     if (node == nullptr) return;
    //     inorderPrint(node->left);
    //     node->data->displayBookInfo();
    //     cout << endl;
    //     inorderPrint(node->right);
    // }

    void printByChuck(Node* node, int chunk, int& counter) {
        auto buttom = [counter, chunk]() -> void {
            cout << string(15, '=') << "Page " << (counter - 1) / chunk + 1 << string(15, '=') << "\n";
            cout << "Press Enter to Next Page...";
            cin.get();
            Show show; show.clear();
        };

        if(chunk < 1 || chunk > bookNumbers) chunk = bookNumbers;
        if(!node) return;

        printByChuck(node->left, chunk, counter);
        cout << string(40, '-') << "\n";
        node->data->displayBookInfo();
        counter++;
        if(counter == this->bookNumbers) {
            buttom();
        }
        else if(counter % chunk == 0) {
            buttom();
        }
        printByChuck(node->right, chunk, counter);
    }

    void postorderHeap(Node* node, Heap& heap, string s) {\
        if(node == nullptr) return;
        postorderHeap(node->left, heap, s);
        postorderHeap(node->right, heap, s);
        auto& book = node->data;
        book->setSimilarity(similarity(book->getTitle(), s));
        heap.insert(book);
    }

    Book* privateFind(Node* node, const Book& b) {
        if (node == nullptr) return nullptr;
    
        if (node->data->getTitle() > b.getTitle())
            return privateFind(node->left, b);  
        else if (node->data->getTitle() < b.getTitle())
            return privateFind(node->right, b); 
        else
            return node->data; 
    }
    

    Book* priavteFindString(Node* node, const string& s) {
        if(node == nullptr) return nullptr;
        if (node->data->getTitle() > s)
            return priavteFindString(node->left, s);  
        else if (node->data->getTitle() < s)
            return priavteFindString(node->right, s); 
        else
            return node->data; 
    }

    void priavteWrite(Node* node, ofstream& out) {
        if(node == nullptr) return;
        priavteWrite(node->left, out);
        priavteWrite(node->right, out);
        out << node->data->getTitle() << "\n";
        out << node->data->getAuthor() << "\n";
        out << node->data->getId() << " " << categoryToChar(node->data->getCategory()) << " "
        << node->data->getYear() << " " << node->data->getCopies() << "\n";
        out << "\n";
    }

    void findByYearP(Node* node, short y, vector<Book*>& v) {
        if(node == nullptr) return;
        findByYearP(node->left, y, v);
        if(node->data->getYear() == y) v.push_back(node->data);
        findByYearP(node->right, y, v);
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

    void printTree(int chunk) {
        int n = 0; 
        printByChuck(root, chunk, n);
    }

    int getbookNumbers() { return bookNumbers; }

    const vector<Book*> searchSimilarity(string s, int n) {
        Heap heap;
        postorderHeap(root, heap, s);
        vector<Book*> ans;
        
        for(int i = 0; i < n; i++) {
            ans.push_back(heap.pop());
        }
        return ans;
    }

    Book* find(const Book& b) {
        return privateFind(root, b);
    }

    Book* find(const string& s) {
        return priavteFindString(root, s);
    }

    void write(ofstream& out) {
        priavteWrite(root, out);
    }

    vector<Book*> findByYear(short y) {
        vector<Book*> v;
        findByYearP(root, y, v);
        return v;
    }
};
