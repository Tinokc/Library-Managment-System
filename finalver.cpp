#include <iostream>
#include <fstream> 
#include <string> 
#include <vector>
#include <sstream> 
#include <set>
#include <iomanip>
#include <cstring>
#include <cctype>
#include <ctime>


using namespace std;
// Define a class for books
class Book {
public:
    string ID;
    string title;
    string author;
    string publisher;
    int year;
    bool availability;
    int timesBorrowed;
    Book() : timesBorrowed(0) {}
};
// Define a class for borrowers
class Borrower {
public:
    string ID;
    string lastName;
    string firstName;
    string contactNumber;
    int numBooksBorrowed;
    vector<Book> borrowedBooks;
    vector<string> borrowedBookIDs;
};
// The purpose of this function is to sort a list of borrowers (people who borrow books)
// alphabetically by their first and last names.
void sortBorrowers(vector<Borrower>& borrowers) {
    int n = borrowers.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            // Inside the nested loop, we check if the first names of the borrowers are the same.
            if (borrowers[j].firstName == borrowers[i].firstName) {
                // If the first names are the same, we sort the borrowers based on their last names.
                if (borrowers[j].lastName < borrowers[i].lastName) {
                    // If borrower j should come before borrower i, we swap them.
                    Borrower temp = borrowers[i];
                    borrowers[i] = borrowers[j];
                    borrowers[j] = temp;
                }
            }
            // If the first names are different, we sort the borrowers based on their first names.
            else {
                if (borrowers[j].firstName < borrowers[i].firstName) {
                    // If borrower j should come before borrower i, we swap them.
                    Borrower temp = borrowers[i];
                    borrowers[i] = borrowers[j];
                    borrowers[j] = temp;
                }
            }
        }
    }
}

// The purpose of this function is to display a list of borrowers in a sorted and formatted manner.
void displayBorrowers(const vector<Borrower>& borrowers) {
    // Create a copy of the original list of borrowers, so that we don't modify the original list when sorting.
    vector<Borrower> sortedBorrowers = borrowers;
    // Sort the copied list of borrowers using the 'sortBorrowers' function.
    sortBorrowers(sortedBorrowers);
    // Print the table header with column names, using 'setw' to set column widths and 'left' to align the text to the left.
    cout << setw(10) << left << "ID"
        << setw(40) << left << "Name"
        << setw(20) << left << "Contact Number"
        << setw(25) << left << "Number of Books Borrowed"
        << endl;
    // Loop through the sorted list of borrowers and print their details in the table.
    for (const auto& borrower : sortedBorrowers) {
        // For each borrower, print their ID, name, contact number, and number of books borrowed.
        // Use 'setw' to set column widths and 'left' to align the text to the left.
        cout << setw(10) << left << borrower.ID
            << setw(40) << left << (borrower.firstName + ", " + borrower.lastName)
            << setw(20) << left << borrower.contactNumber
            << setw(25) << left << borrower.numBooksBorrowed
            << endl;
    }
}

// This function extracts fields from a single line of text, which contains comma-separated values (CSV),
// and stores the fields in the 'fields' array. It returns the number of fields extracted.
int extractFields(const string& line, char fields[10][101]) {
    int numFields = 0;// Counter to keep track of the number of fields extracted
    int currentField = 0;// Current field being extracted
    int currentChar = 0;// Current character in the field being extracted
    bool inQuotes = false;// Flag to check if the current character is inside double quotes
    bool doubleQuotes = false;// Flag to check if the current character is a double quote

    // Loop through each character in the input line
    for (int i = 0; line[i] != '\0'; i++) {
        char c = line[i];// Get the current character
        // If the current character is a double quote
        if (c == '"') {
            inQuotes = !inQuotes;// Toggle the inQuotes flag
            // Check if the previous character was also a double quote and the current character is inside quotes
            if (doubleQuotes == true && inQuotes == true) {
                fields[currentField][currentChar] = c;
                currentChar++;
                doubleQuotes = false;
            }
            else {
                doubleQuotes = true;
            }
        }
        // If the current character is a comma and not inside double quotes
        else if (c == ',' && !inQuotes) {
            fields[currentField][currentChar] = '\0';// Terminate the current field string
            currentField++;// Move on to the next field
            currentChar = 0;// Reset the character index for the next field
            numFields++;// Increment the number of fields extracted
        }
        // If the current character is neither a double quote nor a comma
        else {
            fields[currentField][currentChar] = c;// Add the current character to the current field
            currentChar++;// Move on to the next character in the field
            doubleQuotes = false;// Reset the doubleQuotes flag
        }
    }
    // Terminate the last field string and increment the number of fields extracted
    fields[currentField][currentChar] = '\0';
    numFields++;

    return numFields;// Return the total number of fields extracted
}

void addbook(vector<Book>& books) {

    // This function adds a new book to the library by getting the book details from the user.
    // It takes a reference to a vector of books as a parameter.
    // The function prompts the user to enter the book details such as ID, title, author, publisher, year and availability.
    // Once the user enters the details, the book is added to the vector of books.

    Book book;

    bool idExists;
    do {
        idExists = false;
        do {
            cout << "Enter book ID (at most 10 characters): ";
            cin >> book.ID;
            if (book.ID.length() > 10) {
                cout << "ID must be at most 10 characters." << endl;

            }
        } while (book.ID.length() > 10);
        // check if the entered ID already exists in the books vector

        for (const auto& b : books) {
            if (b.ID == book.ID) {
                idExists = true;
                cout << "ID already exists, please enter a unique ID." << endl;
                break;
            }
        }
    } while (idExists);

    cin.ignore(); // Ignore newline character left in the input buffer

    cout << "Enter book details:" << endl;
    cout << "Title: ";
    getline(cin, book.title);
    cout << "Author: ";
    getline(cin, book.author);
    cout << "Publisher: ";
    getline(cin, book.publisher);
    bool validYear = false;
    do {
        cout << "Year: ";
        cin >> book.year;
        if (book.year > 0) {
            validYear = true;
        }
        else {
            cout << "Invalid year. Please enter a positive number." << endl;
        }
    } while (!validYear);


    book.availability = true;

    books.push_back(book);

    cout << "Book added successfully." << endl;
}




bool caseInsensitiveSearch(const string& str, const string& query) {
    for (size_t i = 0; i <= str.size() - query.size(); ++i) {
        bool match = true;
        for (size_t j = 0; j < query.size(); ++j) {
            if (tolower(str[i + j]) != tolower(query[j])) {
                match = false;
                break;
            }
        }
        if (match) {
            return true;
        }
    }
    return false;
}

void searchBooks(const string& query, const vector<Book>& books) {
    cout << "Search results for \"" << query << "\":" << endl;
    cout << "|************|********************************************************************|***************|" << endl;
    cout << "? " << left << setw(10) << "ID"
        << "? " << setw(72) << "Book details"
        << "? " << setw(13) << "|" << "Availability" << "?" << endl;
    cout << "|************|********************************************************************|***************|" << endl;

    bool found = false;
    for (const auto& book : books) {
        string bookData = book.ID + " " + book.title + " " + book.author + " " + book.publisher;
        if (caseInsensitiveSearch(bookData, query)) {
            found = true;
            cout << "? " << left << setw(10) << book.ID << "? ";
            cout << setw(72) << book.title << "? " << setw(13) << (book.availability ? "Available" : "Not available") << endl;
            cout << "? " << setw(10) << " " << "? " << setw(72) << book.author << "? " << endl;
            cout << "? " << setw(10) << " " << "? " << setw(72) << (book.publisher + " (" + to_string(book.year) + ")") << endl;
            cout << "|************|********************************************************************|***************|" << endl;
        }
    }
    if (!found) {
        cout << "No results found.\n\n";
    }
    else {
        cout << "|************|********************************************************************|***************|" << endl;
    }
}

// This function removes a book with a specific 'bookID' from a vector of 'Book' objects.
void removeBook(vector<Book>& books, const string& bookID) {
    bool bookFound = false;
    // Iterate through the vector of books and find the book with the specified 'bookID'.
    for (size_t i = 0; i < books.size(); ++i) {
        if (books[i].ID == bookID) {
            // Check if the book is available before removing it.
            if (books[i].availability) {
                // Remove the book from the vector by swapping it with the last element and then calling 'pop_back'.
                swap(books[i], books.back());
                books.pop_back();

                // Set the 'bookFound' flag to true and break out of the loop.
                bookFound = true;
                break;
            }
            else {
                cout << "The book is not available for removal." << endl;
                return;
            }
        }
    }
    // Print a message based on whether the book was found and removed.
    if (!bookFound) {
        cout << "Book not found!" << endl;
    }
    else {
        cout << "Book removed successfully." << endl;
    }
}

// This function reads a CSV file containing book records and stores them in a vector of 'Book' objects.
void readCSV_book(const string& filename, vector<Book>& books) {
    fstream inFile; // File stream to read the input file
    string line;// String to store each line read from the input file
    char fields[10][101] = {};// Array to store the extracted fields from each line
    int numFields;// Integer to store the number of fields extracted from each line
    int countRecords = 0; // Counter to keep track of the number of records read
    // open the input file
    inFile.open(filename);
    if (!inFile.is_open()) {
        // If the file cannot be opened, print an error message and return
        cout << "Cannot open file \"" << filename << "\"\n";
        return;
    }
    // Read each line from the input file
    while (getline(inFile, line, '\n')) {
        // Extract fields from the current line using the 'extractFields' function
        numFields = extractFields(line, fields);
        // Create a new 'Book' object and populate its attributes with the extracted fields
        Book book;
        book.ID = fields[0];
        book.title = fields[1];
        book.author = fields[2];
        book.publisher = fields[3];
        book.year = stoi(fields[4]);
        book.availability = true;
        // Add the 'Book' object to the vector of books
        books.push_back(book);
        // Increment the record counter
        countRecords++;
    }
    // Print a message indicating the import is complete
    cout << "Importing book list . . . Done " << endl;
    // Print the number of records imported
    cout << countRecords << " Record(s) imported.\n";
    // Close the input file
    inFile.close();
}
void readCSV_borrowers(const string& filename, vector<Borrower>& borrowers) {
    // This function reads a CSV file containing borrower information and populates a vector of Borrower objects



    fstream inFile;
    string line;
    char fields[10][101] = {};
    int numFields;
    int countRecords = 0;

    // The file is expected to have 5 fields per line: first name, last name, gender, contact number, and email
    inFile.open(filename);
    if (!inFile.is_open()) {
        cout << "Cannot open file \"" << filename << "\"\n";
        return;
    }

    // The function also generates a unique ID for each borrower using a combination of "HKCC" and a random 4-digit number
    const int min_code = 0000;
    const int max_code = 9999;
    string a = "0", b = "00", c = "000";
    srand(time(0));
    set<int> borrowers_id;
    auto it = borrowers_id.begin();
    while (borrowers_id.size() < 500) {
        int code = rand() % (max_code - min_code + 1) + min_code;
        borrowers_id.insert(code);
    }
    it = borrowers_id.begin();

    // read each line of the input file and create a Borrower object for each line
    while (getline(inFile, line, '\n')) {
        numFields = extractFields(line, fields);

        Borrower borrower;
        for (int i = 0; i < min(numFields, 5); i++) {
            string field = fields[i];

            if (i == 0) {
                borrower.firstName = field;
                borrower.lastName = fields[i + 1];
                borrower.numBooksBorrowed = 0;
            }
            else if (i == 1) {
                continue;
            }
            else if (i == 2) {
                borrower.contactNumber = field;
            }
        }
        // assign a unique ID to the borrower
        int value = *it;
        if (value < 1000 && value >= 100) {
            borrower.ID = "HKCC" + a + to_string(value);
        }
        else if (value < 100 && value >= 10) {
            borrower.ID = "HKCC" + b + to_string(value);
        }
        else if (value < 10 && value >= 0) {
            borrower.ID = "HKCC" + c + to_string(value);
        }
        else {
            borrower.ID = "HKCC" + to_string(value);
        }
        ++it;
        // add the borrower to the vector
        borrowers.push_back(borrower);
        countRecords++;
    }

    cout << "Importing borrower list . . . Done " << endl;
    cout << countRecords << " Record(s) imported.\n";
    inFile.close(); //close the file
}
void displayTop5MostBorrowedBooks(const vector<Book>& books) {
    // Check if there are any books in the vector.
    if (books.empty()) {
        cout << "There are no books." << endl;
        return;
    }

    // Create a copy of the books vector to sort it without modifying the original data
    vector<Book> sortedBooks = books;

    // Bubble sort the books based on the timesBorrowed field in descending order
    for (size_t i = 0; i < sortedBooks.size(); ++i) {
        for (size_t j = 0; j < sortedBooks.size() - i - 1; ++j) {
            if (sortedBooks[j].timesBorrowed < sortedBooks[j + 1].timesBorrowed) {
                swap(sortedBooks[j], sortedBooks[j + 1]);
            }
        }
    }

    // Determine the number of books to display
    int numBooksToDisplay = min(5, static_cast<int>(sortedBooks.size()));

    // Display the top 5 most borrowed books (or all books if there are fewer than 5)
    cout << "Top " << numBooksToDisplay << " most borrowed books:" << endl;
    for (int i = 0; i < numBooksToDisplay; ++i) {
        const Book& book = sortedBooks[i];
        cout << (i + 1) << ". ID: " << book.ID << endl;
        cout << "   Title: " << book.title << endl;
        cout << "   Author: " << book.author << endl;
        cout << "   Times Borrowed: " << book.timesBorrowed << endl;
    }
}
// This function searches for a borrower with the given ID in the provided vector of borrowers
void searchBorrowers(const string& borrowerID, const vector<Borrower>& borrowers) {
    bool found = false;
    for (const auto& borrower : borrowers) {
        if (borrower.ID == borrowerID) {
            found = true;
            // print borrower information
            cout << "Borrower ID: " << borrower.ID << endl;
            cout << "Name: " << borrower.lastName << ", " << borrower.firstName << endl;
            cout << "Contact Number: " << borrower.contactNumber << endl;
            cout << "Number of books borrowed: " << borrower.numBooksBorrowed << endl;

            if (borrower.numBooksBorrowed > 0) {
                cout << "Borrowed books:" << endl;
                // print borrowed books
                for (const auto& book : borrower.borrowedBooks) {
                    cout << "- " << book.ID << " " << book.title << " by " << book.author << " " << book.publisher << "(" << book.year << ")" << endl;
                }
            }
            break;
        }
    }
    if (!found) { // if borrower is not found
        cout << "Borrower with ID " << borrowerID << " not found." << endl;
    }
}
// This function capitalizes the first letter of each word in a given string and converts the rest to lowercase
string capitalizeWords(string str) {
    bool newWord = true;
    for (char& c : str) {
        if (newWord) {
            c = toupper(c);
            newWord = false;
        }
        else {
            c = tolower(c);  // convert the rest to lowercase
        }
        if (c == ' ') { // if a space is encountered, the next character is the start of a new word
            newWord = true;
        }
    }
    return str;
}// This function converts a given string to uppercase
string toUpperCase(string str) {
    for (char& c : str) {
        c = toupper(c);
    }
    return str;
}
// This function adds a new borrower to the provided vector of borrowers
void addBorrower(vector<Borrower>& borrowers) {
    // get borrower info from user
    Borrower newBorrower;
    string lastName, firstName, contactNumber;
    bool isValidContactNumber = false;
    do {
        cout << "Enter borrower last name: ";
        cin >> firstName;
        if (firstName.length() > 10) {
            cout << "The last name can not exceed 10 character. Please enter again." << endl;
        }
    } while (firstName.length() > 10);

    do {
        cout << "Enter borrower first name: ";
        cin.ignore(215, '\n');
        getline(cin, lastName);
        if (lastName.length() > 30) {
            cout << "The first name cannot exceed 30 character. Please enter again." << endl;
        }
    } while (lastName.length() > 30);


    // check the contact number to fit the requirement
    while (!isValidContactNumber) {
        cout << "Enter borrower contact number: ";
        cin >> contactNumber;

        if (contactNumber.size() != 8 || (contactNumber[0] != '2' && contactNumber[0] != '3' && contactNumber[0] != '5' && contactNumber[0] != '6' && contactNumber[0] != '9')) {
            cout << "Invalid contact number. Please enter an 8-digit number starting with 2, 3, 5, 6, or 9." << endl;
        }
        else {
            isValidContactNumber = true;
        }
    }

    // generate unique borrower ID
    const int min_code = 0000;
    const int max_code = 9999;
    string a = "0", b = "00", c = "000";
    srand(time(0));
    set<int> borrowers_id;
    auto it = borrowers_id.begin();
    while (borrowers_id.size() < 500) {
        int code = rand() % (max_code - min_code + 1) + min_code;
        borrowers_id.insert(code);
    }
    it = borrowers_id.begin();
    int value = *it;
    if (value < 1000 && value >= 100) {
        newBorrower.ID = "HKCC" + a + to_string(value);
    }
    else if (value < 100 && value >= 10) {
        newBorrower.ID = "HKCC" + b + to_string(value);
    }
    else if (value < 10 && value >= 0) {
        newBorrower.ID = "HKCC" + c + to_string(value);
    }
    else {
        newBorrower.ID = "HKCC" + to_string(value);
    }
    // format and store borrower info in newBorrower object
    newBorrower.firstName = toUpperCase(firstName.substr(0, 10));
    newBorrower.lastName = capitalizeWords(lastName.substr(0, 30));
    newBorrower.contactNumber = contactNumber;
    newBorrower.numBooksBorrowed = 0;
    // add new borrower to borrowers vector and print confirmation message
    borrowers.push_back(newBorrower);
    cout << "Borrower added successfully! Assigned ID: " << newBorrower.ID << endl;
}



void removeBorrower(vector<Borrower>& borrowers) {
    // Get borrower ID from user
    string borrowerID;
    cout << "Enter borrower ID: ";
    cin >> borrowerID;

    // Search for borrower in borrowers vector
    bool found = false;
    for (size_t i = 0; i < borrowers.size(); ++i) {
        if (borrowers[i].ID == borrowerID) {
            found = true;
            // Check if borrower has borrowed books
            if (borrowers[i].numBooksBorrowed > 0) {
                cout << "Borrower has borrowed books! Please return the books before removing the borrower." << endl;
            }
            else {
                // Remove borrower from vector
                borrowers.erase(borrowers.begin() + i);
                cout << "Borrower removed successfully!" << endl;
            }
            break;
        }
    }
    // Borrower not found
    if (!found) {
        cout << "Borrower not found!" << endl;
    }
}
void borrowMultipleBooks(vector<Borrower>& borrowers, vector<Book>& books) {
    string borrowerID, bookID;
    bool borrowerFound = false, bookFound = false;
    int MAX_BORROWED_BOOKS = 5;
    int numBooksToBorrow, booksBorrowed = 0;

    cout << "Enter borrower ID: ";
    cin >> borrowerID;

    // Find borrower
    for (auto& borrower : borrowers) {
        if (borrower.ID == borrowerID) {
            borrowerFound = true;

            // Check if borrower already borrowed maximum number of books
            if (borrower.numBooksBorrowed == MAX_BORROWED_BOOKS) {
                cout << "Borrower has already borrowed the maximum number of books." << endl;
                return;
            }

            cout << "Enter the number of books to borrow: ";
            cin >> numBooksToBorrow;

            while (booksBorrowed < numBooksToBorrow && borrower.numBooksBorrowed < MAX_BORROWED_BOOKS) {
                bookFound = false;
                cout << "Enter book ID: ";
                cin >> bookID;

                // Find book
                for (auto& book : books) {
                    if (book.ID == bookID) {
                        bookFound = true;

                        // Check if book is available
                        if (!book.availability) {
                            cout << "Book is not available for borrowing." << endl;
                            break;
                        }

                        // Borrow book
                        book.availability = false;
                        borrower.numBooksBorrowed++;
                        borrower.borrowedBooks.push_back(book);
                        book.timesBorrowed++;
                        cout << "Book borrowed successfully." << endl;
                        booksBorrowed++;
                        break;
                    }
                }

                if (!bookFound) {
                    cout << "Book not found." << endl;
                }
            }

            if (booksBorrowed < numBooksToBorrow) {
                cout << "Borrower has reached the maximum number of books or there are no more books available to borrow." << endl;
            }

            return;
        }
    }

    if (!borrowerFound) {
        cout << "Borrower not found." << endl;
        return;
    }
}
void displayBooks(const vector<Book>& books) {
    // print header row for book table
    cout << "|************|********************************************************************|***************|" << endl;
    cout << "? " << left << setw(10) << "ID"
        << "? " << setw(72) << "Book details"
        << "? " << setw(13) << "|" << "Availability" << "?" << endl;
    cout << "|************|********************************************************************|***************|" << endl;
    // loop over each book and print its details
    for (const auto& book : books) {
        cout << "? " << left << setw(10) << book.ID << "? ";
        // print book title and availability

        cout << setw(72) << book.title << "? " << setw(13) << (book.availability ? "Available" : "Not available") << endl;
        // print author and publisher/year details
        cout << "? " << setw(10) << " " << "? " << setw(72) << book.author << "? " << endl;
        cout << "? " << setw(10) << " " << "? " << setw(72) << (book.publisher + " (" + to_string(book.year) + ")") << endl;
        // print row divider
        cout << "|************|********************************************************************|***************|" << endl;
    }
}

// This function takes in a vector of Borrower objects and a vector of Book objects.
void returnMultipleBooks(vector<Borrower>& borrowers, vector<Book>& books) {
    string borrowerId, bookId;
    int numBooksToReturn, booksReturned = 0;

    // Get borrower ID
    cout << "Enter borrower ID: ";
    cin >> borrowerId;

    // Find borrower
    int borrowerIndex = -1;
    for (size_t i = 0; i < borrowers.size(); ++i) {
        if (borrowers[i].ID == borrowerId) {
            borrowerIndex = i;
            break;
        }
    }

    // Check if borrower exists
    if (borrowerIndex == -1) {
        cout << "Borrower with ID " << borrowerId << " not found." << endl;
        return;
    }
    if (borrowers[borrowerIndex].numBooksBorrowed == 0) {
        cout << "Borrower with ID " << borrowerId << " has not borrowed any book." << endl;
        return;
    }

    // Get number of books to return from user input
    cout << "Enter the number of books to return: ";
    cin >> numBooksToReturn;

    // Loop through until all requested books have been returned or borrower has no more borrowed books
    while (booksReturned < numBooksToReturn && borrowers[borrowerIndex].numBooksBorrowed > 0) {
        // Get book ID
        cout << "Enter book ID: ";
        cin >> bookId;

        // Find book in library
        int bookIndex = -1;
        for (size_t i = 0; i < books.size(); ++i) {
            if (books[i].ID == bookId) {
                bookIndex = i;
                break;
            }
        }

        // Check if book exists
        if (bookIndex == -1) {
            cout << "Book with ID " << bookId << " not found." << endl;
            continue;
        }

        // Find book in borrower's borrowed books
        int borrowedBookIndex = -1;
        for (size_t i = 0; i < borrowers[borrowerIndex].borrowedBooks.size(); ++i) {
            if (borrowers[borrowerIndex].borrowedBooks[i].ID == bookId) {
                borrowedBookIndex = i;
                break;
            }
        }

        // If borrower has not borrowed book, output message and continue to next iteration
        if (borrowedBookIndex == -1) {
            cout << "Borrower with ID " << borrowerId << " has not borrowed book with ID " << bookId << "." << endl;
            continue;
        }

        // Update book availability
        books[bookIndex].availability = true;

        // Remove book from borrower's borrowed books
        borrowers[borrowerIndex].borrowedBooks.erase(borrowers[borrowerIndex].borrowedBooks.begin() + borrowedBookIndex);

        // Decrease number of books borrowed by borrower
        borrowers[borrowerIndex].numBooksBorrowed--;

        // Output message indicating book has been returned by borrower
        cout << "Book with ID " << bookId << " has been returned by borrower with ID " << borrowerId << "." << endl;

        // Increment number of books returned in current loop iteration
        booksReturned++;
    }
}

void mainMenu() {
    cout << "* Library Management System *" << endl;
    cout << "[1] Manage books" << endl;
    cout << "[2] Manage borrowers" << endl;
    cout << "[3] Borrow book(s)" << endl;
    cout << "[4] Return book(s)" << endl;
    cout << "[5] Useful feature(s) added" << endl;
    cout << "[6] Member List" << endl;
    cout << "[7] Exit" << endl;
    cout << "*****" << endl;
    cout << "Option (1 - 7): ";
}

int main() {
    char bookListChoice, borrowerListChoice;
    vector<Book> books;
    vector<Borrower> borrowers;
    string bookListFile;
    string borrowerListFile;
    string query;
    string searchQuery;//search borrower
    int option;
    int option_q1, option_q2;//Option_Q1 is for Manage book Option_q2 is for Manage borrowers
    cout << "Import book list from file? [Y/N]: ";
    cin >> bookListChoice;
    if (bookListChoice == 'Y' || bookListChoice == 'y') {
        cout << "Path of book list file: ";
        cin.ignore(215, '\n');	// ignore newline character left in the input buffer
        getline(cin, bookListFile);		// Path with space is allowed
        readCSV_book(bookListFile, books);
    }
    cout << "Import borrower list form file? [Y/N]:";
    cin >> borrowerListChoice;
    if (borrowerListChoice == 'N' || borrowerListChoice == 'n') {
        cout << "No borrower list is imported" << endl;
    }
    else if (borrowerListChoice == 'Y' || borrowerListChoice == 'y') {
        cout << "Path of borrower list file:";
        cin.ignore(250, '\n');
        getline(cin, borrowerListFile);
        readCSV_borrowers(borrowerListFile, borrowers);
    }

    int choice;
    while (true) {
        mainMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            // Implement manage books
            do {
                cout << "* Manage Books  *" << endl
                    << " [1] Display books" << endl
                    << " [2] Search book" << endl
                    << " [3] Add book" << endl
                    << " [4] Remove book" << endl
                    << " [5] Back" << endl
                    << "**" << endl;
                cout << "Option (1 - 5): ";
                cin >> option_q1;

                switch (option_q1) {
                case 1: //display books
                    displayBooks(books);
                    break;

                case 2:
                    cout << "Input the book you want to search: ";

                    cin >> query;

                    searchBooks(query, books);
                    break;
                case 3:
                    addbook(books);
                    break;
                case 4:
                    cout << "Input the ID of the book you want to remove: ";
                    string removeBookID;
                    cin >> removeBookID;
                    removeBook(books, removeBookID);
                    break;
                }
            } while (option_q1 != 5);
            break;
        case 2:
            do {
                cout << "* Manage Borrowers *" << endl;
                cout << "[1] Display borrowers" << endl;
                cout << "[2] Search borrowers" << endl;
                cout << "[3] Add borrower" << endl;
                cout << "[4] Remove borrower" << endl;
                cout << "[5] Back" << endl;
                cout << "**" << endl;

                cout << "Option (1 - 5): ";
                cin >> option_q2;

                switch (option_q2) {
                case 1://display borrowers
                    displayBorrowers(borrowers);
                    break;
                case 2:
                    cout << endl << "Input the ID of the borrower you want to search: ";
                    cin >> searchQuery;
                    searchBorrowers(searchQuery, borrowers);
                    break;

                case 3: // add borrower R2.3
                    addBorrower(borrowers);
                    break;

                case 4: //remove borrower R2.4
                    removeBorrower(borrowers);
                    break;


                }
            } while (option_q2 != 5);
            break;
        case 3:
            //borrow book
            borrowMultipleBooks(borrowers, books);
            break;
        case 4:
            // Implement return books
            returnMultipleBooks(borrowers, books);
            break;
        case 5:

            displayTop5MostBorrowedBooks(books);
            break;
        case 6:
            // Implement member list
            cout << "Chong Tinok " << endl;

            break;
        case 7:
            cout << "Are you sure you want to exit? (Y/N): ";
            char confirm;
            cin >> confirm;
            if (confirm == 'Y' || confirm == 'y') {
                return 0;
            }
            break;
        default:
            cout << "Invalid option! Please try again." << endl;
            break;
        }
    }

    return 0;
}