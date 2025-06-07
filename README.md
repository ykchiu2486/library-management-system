# LIBRARY MANAGEMENT SYSTEM

## Features
1. **Book Management**: Complete CRUD operations for books with title, author, ID, category, year, and copy count
2. **User Management**: Add users and track their borrowed books with due dates
3. **Smart Search**: Advanced similarity-based book search using **Levenshtein distance** and **cosine similarity**
4. **Category System**: Books organized by **26 categories** (A-Z) following library classification standards
5. **Borrowing System**: Users can **borrow** and **return** books with automatic due date calculation (30 days)
6. **Overdue Tracking**: Visual indicators for **overdue books** with automatic detection
7. **Year-based Filtering**: Find all books published in a **specific year**
8. **Paginated Display**: Browse large book collections with **customizable page sizes**
9. **Persistent Storage**: All data **saved to files** and **loaded on startup**
10. **Red-Black Tree**: Efficient book storage and retrieval using **self-balancing BST**

## Data Structures & Algorithms
- **Red-Black Tree**: O(log n) book insertion, deletion, and search operations
- **Max Heap**: Priority-based similarity search results
- **Text Similarity**: Combines normalized Levenshtein distance and cosine similarity
- **Date Operations**: Automatic date calculations for borrowing periods

## Usage
To compile and run the program:
```bash
g++ -o library main.cpp
./library
```

#### Notice
Ensure that `ok.txt` (books database) and `user.txt` (users database) are in the same directory as the executable.

### Menu Options
| Option | Description |
|--------|-------------|
| `1` | Search books by title using similarity matching |
| `2` | Display all books with pagination |
| `3` | Show all users and their borrowed books |
| `4` | Borrow a book by title |
| `5` | Return a borrowed book |
| `6` | Add a new book to the database |
| `7` | Add a new user to the system |
| `8` | Find books by publication year |
| `0` | Save all data and exit the program |

### Examples
- **Search books**: Enter partial or full title, get ranked results by similarity
- **Borrow book**: Select user by index, enter book title to borrow
- **Return book**: Select user and book by index to return
- **Add book**: Provide title, author, ID, category (A-Z), year, and copy count
- **Pagination**: Set custom page size to browse through large collections

## File Structure
### Books Database (`ok.txt`)
```
Title
Author
ID CategoryChar Year Copies

[Empty line separator]
```

### Users Database (`user.txt`)
```
Username
NumberOfBorrowedBooks
Title
Author
ID CategoryChar Year Copies DueYear DueMonth DueDay
[Repeat for each borrowed book]
```

## Book Categories <small>(Category enum)</small>
- **A**: General Works
- **B**: Philosophy, Psychology, and Religion
- **C**: History and Related Sciences
- **D**: World History
- **E**: History of the Americas
- **F**: European History
- **G**: Geography, Anthropology, Recreation
- **H**: Social Sciences
- **I**: Literature
- **J**: Political Science
- **K**: Law
- **L**: Education
- **M**: Music
- **N**: Fine Arts
- **O**: Engineering
- **P**: Language and Literature
- **Q**: Science
- **R**: Medicine
- **S**: Agriculture
- **T**: Technology
- **U**: Science
- **V**: Naval Science
- **W**: Medicine
- **X**: Practical Arts
- **Y**: [Custom category]
- **Z**: Bibliography, Library Science, Information Resources

## Key Classes <small>(Object-Oriented Design)</small>
- **Book <small>(base class)</small>**: Core book properties and methods
- **BorrowedBook <small>(derived)</small>**: Extends Book with due date functionality
- **BookDB <small>(Red-Black Tree)</small>**: Efficient book storage and retrieval
- **User <small>(composition)</small>**: User information with borrowed books vector
- **Category <small>(enum)</small>**: Type-safe book categorization
- **Date <small>(utility)</small>**: Date arithmetic and comparison operations
- **Heap <small>(data structure)</small>**: Priority queue for search results

## Advanced Features
- **Similarity Search**: Finds books even with typos or partial matches
- **Automatic Sorting**: Books sorted alphabetically by title in Red-Black Tree
- **Memory Management**: Proper cleanup with destructors and RAII principles
- **Input Validation**: Safe integer and character input with error handling
- **Duplicate Detection**: Prevents adding duplicate books to the database
- **Copy Management**: Tracks available copies and prevents over-borrowing