#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Date.h"
#include "Category.h"
using namespace std;

class Book {
private:
    float similarity = 0;
    short copies = 0;
protected:
    string title;
    string author;
    string id;
    Category category;
    short year;

public:
    Book(string t, string a, string olid, Category c, short y, short cp) : title(t), author(a), id(olid), category(c), year(y), copies(cp) {}
    Book(string t, string a, string olid, Category c, short y) : title(t), author(a), id(olid), category(c), year(y) {}
    void displayBookInfo() const {
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "ID: " << id << endl;
        cout << "Year: " << year << endl;
        cout << "Category: " << categorytoString(category) << endl;
    }

    string getTitle() const { return this->title; } 
    string getAuthor() const { return this->author; }
    string getId() const { return this->id; }
    Category getCategory() const { return this->category; }
    short getYear() const { return this->year; }

    virtual void setSimilarity(float s) final { this->similarity = s; }
    virtual float getSimilarity() final { return this->similarity; }
    virtual void setCopies(int c) final { this->copies = c; }
    virtual int getCopies() const final { return copies; }

    bool operator<(const Book& other) const {
        return title < other.title;
    }

    
};

class BorrowedBook : public Book {
private:
    Date due;

public:
    BorrowedBook(const Book& book) : Book(book) { 
        Date today;
        this->due = today + 30;
    }

    BorrowedBook(const string& t, const string& a, const string& id, Category c, short y) 
    : Book(t, a, id, c, y) {
        Date today;
        this->due = today + 30;
    }

    BorrowedBook(const string& t, const string& a, const string& id, Category c, short y, Date date) 
    : Book(t, a, id, c, y) {
        this->due = date;
    }

    bool isOverdue() const {
        Date today;
        return today > this->due;
    }

    const Date& getDate() {
        return due;
    }

    vector<int> getDateVector() {
        return due.getVector();
    }
};
