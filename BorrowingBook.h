
#include <iostream>
#include <string>
#include <queue>
#include <ctime>
#include "BookFunctions.h"
#include <fstream>
#include "GlobalFunctions.h" // Include the global functions header

using namespace std;

// (I moved the Borrow struct to GlobalFunctions)

// struct Borrow
// {
// private:
//     time_t now = time(0);

// public:
//     string *BookName, *bookId;
//     string dateOfreturning;

//     void setDate()
//     {
//         cout << "Enter the date of the returning day : ";
//         cin.ignore();
//         getline(cin, dateOfreturning);
//     }

//     void saveToFile()
//     {
//         ofstream fileHandler;
//         fileHandler.open("Borrowing_DB.text", ios::app);
//         fileHandler << *bookId << ',' << dateOfreturning << ',' << *BookName << endl;
//         fileHandler.close();
//     }
// };
// queue<Borrow> borrowingQueue;

class BorrowingFunctions
{
public:
    static void loadBorrowedBooks();
    static void BorrowBook();
    static void ShowBorrowedBook();
    static void RemoveBook();
};

void BorrowingFunctions::loadBorrowedBooks()
{
    ifstream fileHandler;
    string line, element, elements[3], bookId;
    int position, index;
    Borrow savedBorrowed;

    fileHandler.open("Borrowing_DB.text");

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

        bookCurrent = bookHead;
        while (bookCurrent->id != elements[0])
        {
            bookCurrent = bookCurrent->nextBook;
        }

        savedBorrowed.bookId = &(bookCurrent->id);
        savedBorrowed.BookName = &(bookCurrent->title);
        savedBorrowed.dateOfreturning = elements[1];

        borrowingQueue.push(savedBorrowed);
    }
    fileHandler.close();
}

void BorrowingFunctions::BorrowBook()
{
    int bookNumberInt = BookFunctions::getBookNumber();
    if (bookNumberInt == -1)
        return;

    bookCurrent = bookHead;
    for (int i = 0; i < bookNumberInt; i++)
    {
        bookCurrent = bookCurrent->nextBook;
    }
    Borrow newBorrow;
    newBorrow.setDate();
    newBorrow.BookName = &(bookCurrent->title);
    newBorrow.bookId = &(bookCurrent->id);
    borrowingQueue.push(newBorrow);

    system("cls");
    cout << "\n\n\n\n\n\t\t\t\t Add Borrow Book Successfully\n\n\t\t\t\tPress Enter to continue. -- ";
    cin.ignore();
    cin.get();
}

void BorrowingFunctions::ShowBorrowedBook()
{
    if (borrowingQueue.empty())
    {
        cout << "------------------- There is No Borrow Book in The Queue -------------------\n";
        cout << "\nPress Enter to continue";
        cin.ignore();
        cin.get();
        system("cls");
        return;
    }

    queue<Borrow> tempQueue = borrowingQueue;

    for (int i = 0; !tempQueue.empty(); i++)
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
        cout << "Book Title : " << *tempQueue.front().BookName << endl;
        cout << "Date of the returning day : " << tempQueue.front().dateOfreturning << endl;
        tempQueue.pop();
        if (tempQueue.empty())
        {
            cout << "\n-------------------End of List----------------------\n";
            cout << "Press Enter to Go to Menu";
            cin.ignore();
            cin.get();
            break;
        }
    }
    system("cls");
}

void BorrowingFunctions::RemoveBook()
{
    system("cls");
    cout << "\n\n\t\t\t\t Remove Borrowed Book\n\n";

    // Display the contents of the borrowingQueue
    queue<Borrow> tempQueue = borrowingQueue;
    while (!tempQueue.empty())
    {
        Borrow borrow = tempQueue.front();
        cout << *borrow.BookName << "\t\t" << borrow.dateOfreturning << endl;
        tempQueue.pop();
    }

    cout << "Enter the book name to remove: ";
    string bookName;
    cin.ignore();
    getline(cin, bookName);

    // Find the book in the queue
    bool isFound = false;
    // Create a new queue to store the remaining books
    queue<Borrow> newQueue;

    // Remove the book from the queue and fill the newQueue with the remaining books
    while (!borrowingQueue.empty())
    {
        if (*borrowingQueue.front().BookName != bookName)
        {
            newQueue.push(borrowingQueue.front());
        }
        else
        {
            isFound = true;
        }
        borrowingQueue.pop();
    }

    // Update borrowingQueue to be the modified queue

    borrowingQueue = newQueue;
    if (!isFound)
    {
        cout << "\n\t\t\t\t Book not found.";
        cin.ignore();
        cin.get();
        return;
    }

    cout << "\n\t\t\t\t Book removed from Borrowed queue successfully.";

    cin.ignore();
    cin.get();
}
