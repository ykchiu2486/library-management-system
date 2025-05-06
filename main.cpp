#include "FileIO.h"
#include "Book.h"
#include "Similarity.h"
#include "BookDB.h"
#include <vector>
#include <utility>
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    BookDB db;
    read("ok.txt", db);
    string s; 
    getline(cin, s);
    const auto v = db.searchSimilarity(s, 5);
    if(v[0]->getSimilarity() < 0.6) 
        cout << "Might not be accurate, try some more specific phrase!\n";
    for(auto i : v) {
        i->displayBookInfo();
        cout << string(64, '-') << "\n";
    }
}