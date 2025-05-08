#include "Book.h"
#include "BookDB.h"
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

class User {
private:
    string name;
    vector<BorrowedBook> BList;

public:
    User(string n) : name(n) {};

    void borrowBook(Book* book) {
        BList.push_back(BorrowedBook(*book));
    }

    void borrowBook(BorrowedBook b) {
        BList.push_back(b);
    }

    Book returnBook(int index) {
        auto book = BList[index];
        BList.erase(BList.begin() + index);
        return book;
    }

    string getName() { return name; }

    void showUser() {
        cout << "Name: " << name << "\n";
        cout << "Books that user borrow: \n";
        int overdue = 0;
        for(auto i : BList) {
            i.displayBookInfo();
            cout << "Due: "; i.getDate().show();
            cout << "\n";
            cout << "Overdue: ";
            if(i.isOverdue()) {
                cout << "yes\n";
                overdue++;
            }
            else cout << "no\n";
        }
        cout << "Overdue count: " << overdue << "\n";
    }

    const vector<BorrowedBook>& getBList() { return BList; }
};
