#ifndef GLOBALFUNCTIONS_H
#define GLOBALFUNCTIONS_H

#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <queue>

using namespace std;

struct Borrow
{
public:
    string *BookName, *bookId;
    string dateOfreturning;

    void setDate()
    {
        cout << "Enter the date of the returning day : ";
        cin.ignore();
        getline(cin, dateOfreturning);
    }

    void saveToFile()
    {
        ofstream fileHandler;
        fileHandler.open("Borrowing_DB.text", ios::app);
        fileHandler << *bookId << ',' << dateOfreturning << ',' << *BookName << endl;
        fileHandler.close();
    }
};
queue<Borrow> borrowingQueue;

struct Book
{
    string id;
    string title;
    string subject;
    string dateOfPub;
    string *authorName = NULL;
    string authorNameToBeSaved;
    Book *nextBook = NULL;

    void setAuthorName()
    {
        if (authorName == NULL)
        {
            authorNameToBeSaved = "Not Assigned yet";
        }
        else
        {
            authorNameToBeSaved = *authorName;
        }
    }

    /// it will save the book's data to the file;
    void saveToFile()
    {
        ofstream fileHandler;
        fileHandler.open("Book_DB.text", ios::app);
        setAuthorName();
        fileHandler << id << ',' << title << ',' << subject << ',' << dateOfPub << ',' << authorNameToBeSaved << endl;
        fileHandler.close();
    }
};
Book *bookTemp = NULL, *bookCurrent = NULL, *bookHead = NULL, *bookTail = NULL;

struct Author
{
    string id;
    string name;
    stack<string *> authorBooksNames;
    Author *nextAuthor = NULL;

    /// it will save the author's data to the file;
    void saveToFile()
    {
        ofstream fileHandler;
        fileHandler.open("Author_DB.text", ios::app);
        fileHandler << id << ',' << name << endl;
        fileHandler.close();
    }
    void saveBooks()
    {
        ofstream fileHandler;
        fileHandler.open("AuthorBooks_DB.text", ios::app);
        while (!authorBooksNames.empty())
        {
            fileHandler << *authorBooksNames.top() << ',' << id << endl;
            authorBooksNames.pop();
        }

        fileHandler.close();
    }
};
Author *authorTemp = NULL, *authorCurrent = NULL, *authorHead = NULL, *authorTail = NULL;

void loadBooks();
void loadAuhors();
void loadAuthorsBooks();
void saveChanges();
void isNumber(string *number);
void showBook(int i);
void searchForBook();
void showAuthor(int i);
void searchForAuthor();
bool isNew(string id);

/// @brief will load the books from the db to the program
void loadBooks()
{
    ifstream fileHandler;
    string line, element, elements[5];
    int position, index;

    fileHandler.open("Book_DB.text");

    while (getline(fileHandler, line))
    {
        position = 0;
        index = 0;
        while (position != -1)
        {
            position = line.find(',');
            element = line.substr(0, position);
            elements[index] = element;
            line = line.substr(position + 1);
            index += 1;
        }

        bookTemp = new Book;

        bookTemp->id = elements[0];
        bookTemp->title = elements[1];
        bookTemp->subject = elements[2];
        bookTemp->dateOfPub = elements[3];

        authorCurrent = authorHead;
        while (authorCurrent != NULL)
        {
            if (authorCurrent->name == elements[4])
            {
                bookTemp->authorName = &authorCurrent->name;
                break;
            }
            authorCurrent = authorCurrent->nextAuthor;
        }

        if (bookHead == NULL)
        {
            bookHead = bookTemp;
            bookTail = bookTemp;
        }
        else
        {
            bookTail->nextBook = bookTemp;
            bookTail = bookTemp;
        }
    }
    fileHandler.close();
}

/// @brief it will load the Authors from the db to the program
void loadAuthors()
{
    ifstream fileHandler;
    string line, element, elements[2];
    int position, index;

    fileHandler.open("Author_DB.text");

    while (getline(fileHandler, line))
    {
        position = 0;
        index = 0;
        while (position != -1)
        {
            position = line.find(',');
            element = line.substr(0, position);
            elements[index] = element;
            line = line.substr(position + 1);
            index += 1;
        }

        authorTemp = new Author;

        authorTemp->id = elements[0];
        authorTemp->name = elements[1];

        if (authorHead == NULL)
        {
            authorHead = authorTemp;
            authorTail = authorTemp;
        }
        else
        {
            authorTail->nextAuthor = authorTemp;
            authorTail = authorTemp;
        }
    }
    fileHandler.close();
}

/// @brief this function will load the books assigned to the authors and link them with the authors
void loadAuthorsBooks()
{
    ifstream fileHandler;
    string line, element, elements[2];
    int position, index;

    fileHandler.open("AuthorBooks_DB.text");

    while (getline(fileHandler, line))
    {
        position = 0;
        index = 0;

        while (position != -1)
        {
            position = line.find(',');
            element = line.substr(0, position);
            elements[index] = element;
            line = line.substr(position + 1);
            index += 1;
        }
        authorCurrent = authorHead;
        while (authorCurrent->id != elements[1] && authorCurrent != NULL)
        {
            authorCurrent = authorCurrent->nextAuthor;
        }
        bookCurrent = bookHead;
        while (bookCurrent->title != elements[0] && bookCurrent != NULL)
        {
            bookCurrent = bookCurrent->nextBook;
        }

        if (bookCurrent != NULL && authorCurrent != NULL)
        {
            authorCurrent->authorBooksNames.push(&bookCurrent->title);
        }
    }
    fileHandler.close();
}

/// @brief this function will save the changes to DB after the program terminates.
void saveChanges()
{

    ofstream fileHandler;
    // openning a file in trunc mode will delete all the things in that file.
    fileHandler.open("Book_DB.text", ios::trunc);
    fileHandler.close();
    fileHandler.open("Author_DB.text", ios::trunc);
    fileHandler.close();
    fileHandler.open("Borrowing_DB.text", ios::trunc);
    fileHandler.close();
    fileHandler.open("AuthorBooks_DB.text", ios::trunc);
    fileHandler.close();

    bookCurrent = bookHead;
    while (bookCurrent != NULL)
    {
        bookCurrent->saveToFile();
        bookCurrent = bookCurrent->nextBook;
    }

    authorCurrent = authorHead;
    while (authorCurrent != NULL)
    {
        authorCurrent->saveToFile();
        authorCurrent->saveBooks();
        authorCurrent = authorCurrent->nextAuthor;
    }
    while (!borrowingQueue.empty())
    {
        borrowingQueue.front().saveToFile();
        borrowingQueue.pop();
    }
}

void isNumber(string *number)
{
    string tempNumber = *number;
    bool isTrue = false;
    if (tempNumber == " ")
    {
        tempNumber = "a";
    }
    do
    {
        for (int i = 0; i < tempNumber.length(); i++)
        {
            if (!('0' <= tempNumber[i] && tempNumber[i] <= '9'))
            {
                isTrue = false;
                cout << "Enter a Correct Number\n";
                cin >> tempNumber;
                isNumber(&tempNumber);
            }
            isTrue = true;
        }
    } while (!isTrue);
    *number = tempNumber;
}

void showBook(int i)
{
    bookCurrent = bookHead;
    for (int j = 0; i > j; j++)
    {
        bookCurrent = bookCurrent->nextBook;
    }
    cout << "Book id: " << bookCurrent->id << endl;
    cout << "Book Title: " << bookCurrent->title << endl;
    if (bookCurrent->authorName == nullptr)
    {
        cout << "Author Name: Not Assign Yet" << endl;
    }
    else
    {
        cout << "Author Name: " << bookCurrent->authorName << endl;
    }
    cout << "Book subject: " << bookCurrent->subject << endl;
    cout << "Publication Date: " << bookCurrent->dateOfPub << endl;
}

void searchForBook()
{
    int intChoice;
    do
    {
        system("cls");
        cout << "Choose what you want to search for:" << endl;
        cout << "1- Book id" << endl;
        cout << "2- Book Title" << endl;
        cout << "3- Book subject" << endl;
        cout << "4- Publication Date" << endl;
        cout << "5- Exit" << endl;

        string information;
        bool isMore = false;
        bool isFound = false;
        string choice;
        cout << "Enter your choice: ";
        cin >> choice;
        isNumber(&choice);
        intChoice = stoi(choice);

        switch (intChoice)
        {
        case 1:
            system("cls");
            cout << "Enter Id You want to search for: ";
            cin.ignore();
            getline(cin, information);
            isNumber(&information);
            system("cls");

            bookCurrent = bookHead;
            for (int i = 0; bookCurrent != NULL; i++)
            {
                if (bookCurrent->id == information)
                {
                    isFound = true;
                    showBook(i);
                    if (isMore)
                    {
                        cout << "================================================" << endl;
                    }
                    isMore = true;
                    cout << "\t\t\t\t \nPress Enter to continue  \n";
                    cin.get();
                }
                bookCurrent = bookCurrent->nextBook;
            }
            if (!isFound)
            {
                cout << "\t\t\t\t Not Found  \n";
                cout << "\t\t\t\t \nPress Enter to continue  \n";
                cin.get();
            }
            break;
        case 2:
            system("cls");
            cout << "Enter Book Title You want to search for: ";
            cin.ignore();
            getline(cin, information);
            system("cls");

            bookCurrent = bookHead;
            for (int i = 0; bookCurrent != NULL; i++)
            {
                if (bookCurrent->title == information)
                {
                    isFound = true;
                    showBook(i);
                    if (isMore)
                    {
                        cout << "================================================" << endl;
                    }
                    isMore = true;
                    cout << "\t\t\t\t \nPress Enter to continue  \n";
                    cin.get();
                }
                bookCurrent = bookCurrent->nextBook;
            }
            if (!isFound)
            {
                cout << "\t\t\t\t Not Found  \n";
                cout << "\t\t\t\t \nPress Enter to continue  \n";
                cin.get();
            }
            break;
        case 3:
            system("cls");
            cout << "Enter Book subject You want to search for: ";
            cin.ignore();
            getline(cin, information);
            system("cls");

            bookCurrent = bookHead;
            for (int i = 0; bookCurrent != NULL; i++)
            {
                if (bookCurrent->subject == information)
                {
                    isFound = true;
                    showBook(i);
                    if (isMore)
                    {
                        cout << "================================================" << endl;
                    }
                    isMore = true;
                    cout << "\t\t\t\t \nPress Enter to continue  \n";
                    cin.get();
                }
                bookCurrent = bookCurrent->nextBook;
            }
            if (!isFound)
            {
                cout << "\t\t\t\t Not Found  \n";
                cout << "\t\t\t\t \nPress Enter to continue  \n";
                cin.get();
            }
            break;
        case 4:
            system("cls");
            cout << "Enter Publication Date You want to search for: ";
            cin.ignore();
            getline(cin, information);
            system("cls");

            bookCurrent = bookHead;
            for (int i = 0; bookCurrent != NULL; i++)
            {
                if (bookCurrent->dateOfPub == information)
                {
                    isFound = true;
                    showBook(i);
                    if (isMore)
                    {
                        cout << "================================================" << endl;
                    }
                    isMore = true;
                    cout << "\t\t\t\t \nPress Enter to continue  \n";
                    cin.get();
                }
                bookCurrent = bookCurrent->nextBook;
            }
            if (!isFound)
            {
                cout << "\t\t\t\t Not Found  \n";
                cout << "\t\t\t\t \nPress Enter to continue  \n";
                cin.get();
            }
            break;
        case 5:
            return;
        default:
            cout << "Invalid choice. Please try again." << endl;
            cin.get();
        }
    } while (true);
}

void showAuthor(int i)
{
    authorCurrent = authorHead;
    for (int j = 0; j < i; j++)
    {
        authorCurrent = authorCurrent->nextAuthor;
    }

    cout << "Author id: " << authorCurrent->id << endl;
    cout << "Author Name: " << authorCurrent->name << endl;
    // cout << "Number of Books: " << authorCurrent->numberOfBooksOfAuthor << endl;
}

void searchForAuthor()
{
    int intChoice;
    do
    {
        system("cls");
        cout << "Choose what you want to search for:" << endl;
        cout << "1- Author id" << endl;
        cout << "2- Author Name" << endl;
        cout << "3- Exit" << endl;

        string information;
        bool isMore = false;
        bool isFound = false;
        string choice;
        cout << "Enter your choice: ";
        cin >> choice;
        isNumber(&choice);
        intChoice = stoi(choice);

        switch (intChoice)
        {
        case 1:
            system("cls");
            cout << "Enter Id You want to search for: ";
            cin.ignore();
            getline(cin, information);
            isNumber(&information);
            system("cls");

            authorCurrent = authorHead;
            for (int i = 0; authorCurrent != NULL; i++)
            {
                if (authorCurrent->id == information)
                {
                    isFound = true;
                    showAuthor(i);
                    if (isMore)
                    {
                        cout << "================================================" << endl;
                    }
                    isMore = true;
                    cout << "\t\t\t\t \nPress Enter to continue  \n";
                    cin.get();
                }
                authorCurrent = authorCurrent->nextAuthor;
            }
            if (!isFound)
            {
                cout << "\t\t\t\t Not Found  \n";
                cout << "\t\t\t\t \nPress Enter to continue  \n";
                cin.get();
            }
            break;
        case 2:
            system("cls");
            cout << "Enter Author Name You want to search for: ";
            cin.ignore();
            getline(cin, information);
            system("cls");

            authorCurrent = authorHead;
            for (int i = 0; authorCurrent != NULL; i++)
            {
                if (authorCurrent->name == information)
                {
                    isFound = true;
                    showAuthor(i);
                    if (isMore)
                    {
                        cout << "================================================" << endl;
                    }
                    isMore = true;
                    cout << "\t\t\t\t \nPress Enter to continue  \n";
                    cin.get();
                }
                authorCurrent = authorCurrent->nextAuthor;
            }
            if (!isFound)
            {
                cout << "\t\t\t\t Not Found  \n";
                cout << "\t\t\t\t \nPress Enter to continue  \n";
                cin.get();
            }
            break;
        case 3:
            return;
        default:
            cout << "Invalid choice. Please try again." << endl;
            cin.get();
        }
    } while (true);
}

/// search if you have book id before
bool isNew(string id)
{
    authorCurrent = authorHead;
    while (authorCurrent != NULL)
    {
        if (authorCurrent->id == id)
        {

            cout << "This Id is already exist\n";
            cout << "\nPress Enter to continue";
            cin.ignore();
            cin.get();
            system("cls");
            return false;
        }
        authorCurrent = authorCurrent->nextAuthor;
    }
    return true;
}

#endif
