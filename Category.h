#pragma once
#include <string>
#include <stdexcept> 
enum class Category {
    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K,
    L,
    M,
    N,
    O,
    P,
    Q,
    R,
    S,
    T,
    U,
    V,
    W,
    X,
    Y,
    Z
};

static const std::string categorytoString(Category c) {
    switch (c) {
        case Category::A: return "General Works";
        case Category::B: return "Philosophy, Psychology, and Religion";
        case Category::C: return "History and Related Sciences";
        case Category::D: return "World History";
        case Category::E: return "History of the Americas";
        case Category::F: return "European History";
        case Category::G: return "Geography, Anthropology, Recreation";
        case Category::H: return "Social Sciences";
        case Category::J: return "Political Science";
        case Category::K: return "Law";
        case Category::L: return "Education";
        case Category::M: return "Music";
        case Category::N: return "Fine Arts";
        case Category::P: return "Language and Literature";
        case Category::Q: return "Science";
        case Category::R: return "Medicine";
        case Category::S: return "Agriculture";
        case Category::T: return "Technology";
        case Category::U: return "Science";
        case Category::V: return "Naval Science";
        case Category::Z: return "Bibliography, Library Science, Information Resources";
        case Category::I: return "Literature";
        case Category::W: return "Medicine";
        case Category::O: return "Engineering";
        case Category::X: return "Practical Arts";
        default: return "Unknown category";
    }
}

static Category chartoCategory(char c) {
    switch (c) {
        case 'A': return Category::A;
        case 'B': return Category::B;
        case 'C': return Category::C;
        case 'D': return Category::D;
        case 'E': return Category::E;
        case 'F': return Category::F;
        case 'G': return Category::G;
        case 'H': return Category::H;
        case 'J': return Category::J;
        case 'K': return Category::K;
        case 'L': return Category::L;
        case 'M': return Category::M;
        case 'N': return Category::N;
        case 'P': return Category::P;
        case 'Q': return Category::Q;
        case 'R': return Category::R;
        case 'S': return Category::S;
        case 'T': return Category::T;
        case 'U': return Category::U;
        case 'V': return Category::V;
        case 'Z': return Category::Z;
        case 'I': return Category::I;
        case 'W': return Category::W;
        case 'O': return Category::O;
        case 'X': return Category::X;
        case 'Y': return Category::Y;
        default:
            return Category::A;
    }
}

static char categoryToChar(Category cat) {
    switch (cat) {
        case Category::A: return 'A';
        case Category::B: return 'B';
        case Category::C: return 'C';
        case Category::D: return 'D';
        case Category::E: return 'E';
        case Category::F: return 'F';
        case Category::G: return 'G';
        case Category::H: return 'H';
        case Category::I: return 'I';
        case Category::J: return 'J';
        case Category::K: return 'K';
        case Category::L: return 'L';
        case Category::M: return 'M';
        case Category::N: return 'N';
        case Category::O: return 'O';
        case Category::P: return 'P';
        case Category::Q: return 'Q';
        case Category::R: return 'R';
        case Category::S: return 'S';
        case Category::T: return 'T';
        case Category::U: return 'U';
        case Category::V: return 'V';
        case Category::W: return 'W';
        case Category::X: return 'X';
        case Category::Y: return 'Y';
        case Category::Z: return 'Z';
        default: return 'A';
    }
}
