#pragma once
#include <string>
#include <vector>
#include "Book.h" 
#include "Search.h"
using namespace std;

class User {

    string name; // must be unique
    vector<BorrowedBook> borrowedList; // max to 50

public:

    User(const string& userName) : name(userName) {} 



    bool borrow(const Book& book) { 

        if (this->borrowedList.size() >= 50) return false;
        BorrowedBook b(book);
        int pos = 0;
        while (pos < borrowedList.size() && borrowedList[pos].getTitle() < b.getTitle()) {
            ++pos;
        }
        borrowedList.insert(borrowedList.begin() + pos, b);
        return true;
    }

    bool returnBook(const Book& targetBook) { 

        long long pos = binarySearch<BorrowedBook, Book>(
            borrowedList, targetBook, 0, borrowedList.size(),
            [](const BorrowedBook& b) { return b.getTitle(); }, 
            [](const Book& b) { return b.getTitle(); } 

        );

        if (pos < 0) return false;
        borrowedList.erase(borrowedList.begin() + pos);
        return true;
    }

    string getName() const { return this->name; } 
    int quota() const { return 50 - static_cast<int>(borrowedList.size()); } 
};