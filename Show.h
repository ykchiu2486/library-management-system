#pragma once
#include <iostream>
using namespace std;

struct Show {
    void clear() {
        cout << "\033[2J\033[H";
    }

    void showDefaultOptions() {
        cout << "1. search book by title\n";
        cout << "2. show all books\n";
        cout << "3. show users\n";
        cout << "4. borrow books by title\n";
        cout << "5. return books\n";
        cout << "6. Add book to db\n";
        cout << "7. Add user\n";
        cout << "8. clear the terminal\n";
        cout << "0. exit the system\n";
    }

    void greeting() {
        cout << "Welcome using the shitty library management system\n";
    }
};