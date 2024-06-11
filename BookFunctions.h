#ifndef BOOKFUNCTIONS_H
#define BOOKFUNCTIONS_H

#include <iostream>
#include <string>

#include "BookFunctions.h"
#include "GlobalFunctions.h" // Include the global functions header
#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>
using namespace std;

class BookFunctions
{
public:
    static void showAllBooks();
    static bool isNew(string id);
    static void addBook();
    static int getBookNumber();
    static void updateBook();
    static void RemoveABook();
    static void removeBookFromDB(Book *target);
    static void DeleteAllBooks();
};

void BookFunctions::showAllBooks()
{
    if (bookHead == NULL)
    {
        cout << "------------------- No Books yet -------------------\n";
        cout << "\nPress Enter to continue";
        cin.ignore();
        cin.get();
        system("cls");
    }
    else
    {
        bookCurrent = bookHead;
        for (int i = 0; bookCurrent != NULL; i++)
        {
            if (i == 0)
            {
                cout << "\n--------------------All Books-----------------------\n";
            }
            else
            {
                cout << "\n\n";
            }
            cout << "                  Book Number " << i + 1 << "                  \n";
            cout << "Book id: " << bookCurrent->id << endl;
            cout << "Book Title: " << bookCurrent->title << endl;

            if (bookCurrent->authorName == NULL)
            {
                cout << "Author Name: Not Assigned Yet" << endl;
            }
            else
            {
                cout << "Author Name: " << *(bookCurrent->authorName) << endl;
            }
            cout << "Book subject: " << bookCurrent->subject << endl;
            cout << "Publication Date: " << bookCurrent->dateOfPub << endl;
            if (bookCurrent->nextBook == NULL)
            {
                cout << "\n-------------------End of List----------------------\n";
                cout << "Press Enter to Go to Menu";
                if(i == 0){
                    cin.ignore();
                }
                cin.get();
            }
            else
            {
                cout << "\nPress Enter to continue";
                if(i == 0){
                    cin.ignore();
                }
                cin.get();
            }
            bookCurrent = bookCurrent->nextBook;
        }
    }
    system("cls");
}

bool BookFunctions::isNew(string id)
{
    bookCurrent = bookHead;
    while (bookCurrent != NULL)
    {
        if (bookCurrent->id == id)
        {
            cout << "This Id is already exist\n";
            cout << "\nPress Enter to continue";
            cin.ignore();
            system("cls");
            return false;
        }
        bookCurrent = bookCurrent->nextBook;
    }
    return true;
}

void BookFunctions::addBook()
{
    cout << "\n- Enter book Details -\n";

    string id;
    cout << "Book Id: ";
    cin.ignore();
    getline(cin, id);

    isNumber(&id);

    if (!isNew(id))
    {
        return;
    }

    bookTemp = new Book;
    bookTemp->id = id;

    cout << "Book Title: ";
    getline(cin, bookTemp->title);

    cout << "Enter Book subject: ";
    getline(cin, bookTemp->subject);

    cout << "Enter Publication Date: ";
    getline(cin, bookTemp->dateOfPub);
    system("cls");

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

    cout << "\n\n\n\n\n\t\t\t\t Book added Successfully\n\n\t\t\t\tPress Enter to continue.";
    cin.get();
}

int BookFunctions::getBookNumber()
{

    if (bookHead == NULL)
    {
        cout << "------------------- No Books yet -------------------\n";
        cout << "\nPress Enter to continue";
        cin.ignore();
        cin.get();
        system("cls");
        return -1;
    }

    string bookNumber;
    int numberOfBooks = 0;
    bookCurrent = bookHead;

    cout << "\n--------------------All Books-----------------------\n";
    for (int i = 0; bookCurrent != NULL; i++)
    {
        cout << i + 1 << ". Book title: " << bookCurrent->title << endl;
        numberOfBooks++;
        bookCurrent = bookCurrent->nextBook;
    }

    cout << "\n\nChoose a Book, or press 0 to exit: ";
    int bookNumberInt;
    do
    {
        cin >> bookNumber;
        isNumber(&bookNumber);
        bookNumberInt = stoi(bookNumber);

    } while (!(0 < bookNumberInt && bookNumberInt < numberOfBooks));
    return (bookNumberInt - 1);
}

/// update a book
void BookFunctions::updateBook()
{
    int bookNumberInt = BookFunctions::getBookNumber();
    if (bookNumberInt == -1)
        return;

    bookCurrent = bookHead;
    for (int i = 0; i < bookNumberInt; i++)
    {
        bookCurrent = bookCurrent->nextBook;
    }

    char Choice;
    do
    {
        system("cls");
        cout << "What do you  want to update" << endl;
        cout << "1- Book Title: " << endl;
        cout << "2- Book subject: " << endl;
        cout << "3- Publication Date: " << endl;
        cout << "4- Exit" << endl;
        cout << "Enter your choice: ";
        cin >> Choice;
        system("cls");

        string newId;
        string newTitle;
        switch (Choice)
        {
        case '1':
            cout << "Book Title: ";
            cin.ignore();
            getline(cin, newTitle);
            bookCurrent->title = newTitle;
            break;
        case '2':
            cout << "Book subject: ";
            cin >> bookCurrent->subject;
            break;
        case '3':
            cout << "Publication Date: ";
            cin >> bookCurrent->dateOfPub;
            break;
        case '4':
            break;
        default:
            cout << "Invalid choice" << endl;
            break;
        }
    } while (Choice != '4');
    system("cls");
    cout << "\n\n\n\n\n\t\t\t\t Book Updated Successfully\n\n\t\t\t\tPress Enter to continue.";
    cin.ignore();
    cin.get();
}

/// remove a book
void BookFunctions::RemoveABook()
{
    int bookNumberInt = BookFunctions::getBookNumber();
    if (bookNumberInt == -1)
        return;

    bookCurrent = bookHead;
    if (bookHead == bookTail)
    {

        delete bookHead;
        bookHead = NULL;
        bookTail = NULL;
    }
    else if (bookNumberInt == 0)
    {
        bookTemp = bookHead;
        bookHead = bookHead->nextBook;

        delete bookTemp;
    }
    else
    {
        for (int i = 0; i < bookNumberInt - 1; i++)
        {
            bookCurrent = bookCurrent->nextBook;
        }

        if (bookCurrent->nextBook == bookTail)
        {
            bookTemp = bookTail;
            bookTail = bookCurrent;
            bookTail->nextBook = NULL;

            delete bookTemp;
        }
        else
        {
            bookTemp = bookCurrent->nextBook;
            bookCurrent->nextBook = bookTemp->nextBook;

            delete bookTemp;
        }
    }

    system("cls");
    cout << "\n\n\n\n\n\t\t\t\t Book Deleted Successfully\n\n\t\t\t\tPress Enter to continue.";
    cin.get();
}

/// delete all books
void BookFunctions::DeleteAllBooks()
{
    cout << "If you want to delete all Book press 1 , else Enter Anything else \n";
    char choice;
    cin >> choice;
    if (choice == '1')
    {
        bookCurrent = bookHead;
        for (int i = 0; bookCurrent != NULL; i++)
        {
            bookTemp = bookCurrent;
            bookCurrent = bookCurrent->nextBook;
            delete bookTemp;
        }
        bookHead = NULL;
        bookTail = NULL;

        cout << "\n\n\n\n\n\t\t\t\tAll Book Deleted Successfully\n";
        Sleep(1000);
        system("cls");
    }

    system("cls");
    cin.get();
}

#endif
