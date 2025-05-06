#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include "Book.h"
#include "Category.h"
#include "BookDB.h"

void read(const std::string& filename, BookDB& rbt) {
    std::ifstream in(filename);
    if (!in.is_open()) {
        std::cerr << "Cannot open file: " << filename << "\n";
        exit(1);
    }

    std::string title, author, line, id;
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
}