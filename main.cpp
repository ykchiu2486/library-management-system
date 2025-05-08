#include <iostream>
#include "BookDB.h"
#include "FileIO.h"
#include "Category.h"
#include <limits>
using namespace std;

int safeIntInput(const string& prompt, int min, int max) {
    int value;
    bool validInput = false;

    do {
        cout << prompt;
        if (cin >> value && value >= min && value <= max) {
            validInput = true;
        } else {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "Invalid input. Please enter an integer between " << min << " and " << max << ".\n";
        }
    } while (!validInput);

    return value;
}

int main() {
    Show show;
    BookDB db;
    vector<User> users;
    readBook("ok.txt", db);
    readUser("user.txt", users);

    auto case1 = [&]() {
        show.clear();
        int result = safeIntInput("How many results you want to see: ", 0, db.getbookNumbers());
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        cout << "The Titile You Want to Search: ";
        string title; getline(cin, title);
        auto ans = db.searchSimilarity(title, result);
        for(auto i : ans) {
            cout << string(30, '-') << "\n";
            i->displayBookInfo();
        }
        cout << string(30, '=') << "\n";
        cout << "Press Enter to continue..";
        cin.get();
    };

    auto case2 = [&]() {
        show.clear();
        cout << "There are " << db.getbookNumbers() << " books. \nHow many books do you want to show in a page: ";
        int bookPerPage = safeIntInput("", 1, db.getbookNumbers());
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        show.clear();
        db.printTree(bookPerPage);
    };

    auto case3 = [&]() {
        show.clear();
        for(auto i : users) {
            cout << string(30, '-') << "\n";
            i.showUser();
        }
        cout << string(30, '=') << "\n";
        cout << "Press Enter to continue..";
        cin.get();
    };

    auto case4 = [&]() {
        show.clear();
        for(int i = 0; i < users.size(); i++) {
            cout << "[Index " << i << "] ";
            cout << users[i].getName() << "\n";
        }
        int index = safeIntInput("Please choose a user by index: ", 0, users.size() - 1);
        string title;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "The title of the book: "; getline(cin, title);
        auto book = db.find(title);
        if(book == nullptr) return;
        if(book->getCopies() < 1) {
            cout << "Not enough copies!\n";
            return;
        }
        book->setCopies(book->getCopies() - 1);
        users[index].borrowBook(book);
    };

    auto case5 = [&]() {
        show.clear();
        for(int i = 0; i < users.size(); i++) {
            cout << "[Index " << i << "] ";
            cout << users[i].getName() << "\n";
        }
        int index = safeIntInput("Please use choose a user by index: ", 0, users.size() - 1);
        auto& blist = users[index].getBList();
        for(int i = 0; i < blist.size(); i++) {
            cout << "[Index " << i << "] ";
            cout << blist[i].getTitle() << "\n";
        }
        int bookIndex = safeIntInput("Please use choose a book by index: ", 0, blist.size() - 1);
        Book* book = db.find(blist[bookIndex]);
        book->setCopies(book->getCopies() + 1);
        users[index].returnBook(bookIndex);
    };


    auto case6 = [&]() {
        show.clear();
        string title, author, id;
        char category; short year, copies;
        cout << "Title: "; getline(cin, title);
        cout << "Author: "; getline(cin, author);
        cout << "ID: "; cin >> id;
        cout << "Category: "; category = safeIntInput("", 65, 90);
        cout << "Year; "; year = safeIntInput("", 0, 2030);
        cout << "Copies: "; copies = safeIntInput("", 1, 10);
        bool ans = db.addBook(new Book(title, author, id, chartoCategory(category), year, copies));
        cout << (ans ? "Success" : "Fail") << "\n";
        cout << string(30, '=') << "\n";
        cout << "Press Enter to continue..";
        cin.get();
    };

    auto case7 = [&]() {
        show.clear();
        string name;
        cout << "Name: "; getline(cin, name);
        users.push_back(User(name));
    };

    auto case0 = [&]() {
        writeBooks("ok.txt", db);
        writeUsers("user.txt", users);
        exit(0);
    };

    while(true) {
        show.clear();
        show.greeting();
        show.showDefaultOptions();
        int command = safeIntInput("Please input a command: ", 0, 8);
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch (command) {
            case 1:
                case1();
                break;
            case 2:
                case2();
                break;
            case 3:
                case3();
                break;
            case 4:
                case4();
                break;
            case 5:
                case5();
                break;
            case 6:
                case6();
                break;
            case 7:
                case7();
                break;
            case 0:
                case0();
                break;
            default:
                break;
        }
    }

}