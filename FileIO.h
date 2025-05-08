#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "User.h"
#include "Book.h"
#include "Category.h"
#include "BookDB.h"

void readBook(const std::string& filename, BookDB& rbt) {
    ifstream in(filename);
    if (!in.is_open()) {
        std::cerr << "Cannot open file: " << filename << "\n";
        exit(1);
    }

    string title, author, line, id;
    char category;
    short year, copies;

    while (getline(in, title) && 
           getline(in, author) && 
           getline(in, line)) {
        std::istringstream iss(line);
        if (iss >> id >> category >> year >> copies) {
            auto ans = rbt.addBook(new Book(title, author, id, chartoCategory(category), year, copies));
            if(!ans) cerr << "[Warning] Duplicate Book!\n"; 
        };
        getline(in, line);
    }
    in.close();
}

void readUser(string filename, vector<User>& users) {
    ifstream in(filename);
    if (!in.is_open()) {
        cerr << "Cannot open file: " << filename << "\n";
        exit(1);
    }

    string name;
    while (getline(in, name)) {
        if (name.empty()) continue;

        int books;
        string books_line;
        if (!getline(in, books_line)) break;  
        stringstream ss(books_line);
        ss >> books;

        User user(name);
        for (int i = 0; i < books; ++i) {
            string title, author, line;
            string id;
            char category;
            short year, copies;
            short y, m, d;

            if (!getline(in, title)) break;
            if (!getline(in, author)) break;
            if (!getline(in, line)) break;

            istringstream iss(line);
            if (iss >> id >> category >> year >> copies >> y >> m >> d) {
                BorrowedBook bbook(title, author, id, chartoCategory(category), year, Date(y, m, d));
                user.borrowBook(bbook);
            } else {
                cerr << "Invalid book format for user: " << name << "\n";
            }
        }
        users.push_back(user);
    }

    in.close();
}


void writeBooks(string filename, BookDB& db) {
    ofstream out(filename);
    db.write(out);
    out.close();
}

void writeUsers(string filename, vector<User> users) {
    ofstream out(filename);
    for(auto us : users) {
        out << us.getName() << "\n" << us.getBList().size() << "\n";
        for(auto book : us.getBList()) {
            out << book.getTitle() << "\n";
            out << book.getAuthor() << "\n";
            out << book.getId() << " " << categoryToChar(book.getCategory()) << " " << book.getYear() << " " << book.getCopies() << " ";
            for(auto i : book.getDateVector() ) {
                out << i << " ";
            }
            out << "\n";
        }
    }
}