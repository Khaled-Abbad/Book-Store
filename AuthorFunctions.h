#ifndef AUTHORFUNCTIONS_H
#define AUTHORFUNCTIONS_H

#include <iostream>
#include <string>

#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>
using namespace std;
#include <vector> // Include the vector header

#include "AuthorFunctions.h"
#include "BookFunctions.h"
#include "GlobalFunctions.h" // Include the global functions header
class AuthorFunctions
{
public:
    void showAllAuthors();
    bool isNew(string id);
    void addAuthor();
    int getAuthorNumber();
    void AssignABookToAuthor();
    void RemoveBooksFromAuthor();
    void updateAuthor();
    void RemoveAnAuthor();
    void DeleteAllAuthors();
};

void AuthorFunctions::showAllAuthors()
{
    if (authorHead == NULL)
    {
        cout << "------------------- No Authors yet -------------------\n";
        cout << "\nPress Enter to continue";
        cin.ignore();
        cin.get();
        system("cls");
    }
    else
    {
        authorCurrent = authorHead;
        for (int i = 0; authorCurrent != NULL; i++)
        {
            if (i == 0)
            {
                cout << "\n--------------------All Authors-----------------------\n";
            }
            else
            {
                cout << "\n\n";
            }
            cout << "                  Author Number " << i + 1 << "                  \n";
            cout << "Author id: " << authorCurrent->id << endl;
            cout << "Author name: " << (authorCurrent->name) << endl;
            if (!authorCurrent->authorBooksNames.empty())
            {
                cout << "Author Books Title: " << endl;
                stack<string *> tempAuthorBooksNames = authorCurrent->authorBooksNames;
                int counter = 0;
                while (!tempAuthorBooksNames.empty())
                {
                    cout << ++counter << ". title : " << *(tempAuthorBooksNames.top()) << endl;
                    tempAuthorBooksNames.pop();
                }
            }
            else
            {
                cout << "This Author doesn't have books yet" << endl;
            }
            if (authorCurrent->nextAuthor == NULL)
            {
                cout << "-------------------End of List----------------------\n";
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
            authorCurrent = authorCurrent->nextAuthor;
        }
        system("cls");
    }
}

bool AuthorFunctions::isNew(string id)
{
    authorCurrent = authorHead;
    while (authorCurrent != NULL)
    {
        if (authorCurrent->id == id)
        {
            cout << "This Id is already exist\n";
            cout << "\nPress Enter to continue";
            cin.ignore();
            system("cls");
            return false;
        }
        authorCurrent = authorCurrent->nextAuthor;
    }
    return true;
}

void AuthorFunctions::addAuthor()
{
    cout << "\n- Enter Author Details -\n";
    string id;
    cout << "Author Id: ";
    cin.ignore();
    getline(cin, id);
    isNumber(&id);
    if (!isNew(id))
    {
        return;
    }

    authorTemp = new Author;
    authorTemp->id = id;
    cout << "Author name: ";
    getline(cin, authorTemp->name);

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

    system("cls");
    cout << "\n\n\n\n\n\t\t\t\t Author Added Successfully\n\n\t\t\t\tPress Enter to continue.";
    cin.get();
}

int AuthorFunctions::getAuthorNumber()
{
    if (authorHead == NULL)
    {
        cout << "------------------- No Authors yet -------------------\n";
        cout << "\nPress Enter to continue";
        cin.ignore();
        cin.get();
        system("cls");
        return -1;
    }
    string authorNumber;
    cout << "\n--------------------All Authors-----------------------\n";

    authorCurrent = authorHead;
    int counterOfAuthors = 0;
    for (int i = 0; authorCurrent != NULL; i++)
    {
        cout << i + 1 << ". Author Name: " << (authorCurrent->name) << endl;
        authorCurrent = authorCurrent->nextAuthor;
        counterOfAuthors++;
    }
    cout << "\n\nChoose an Author ";
    int authorNumberInt;
    do
    {
        cin >> authorNumber;
        isNumber(&authorNumber);
        authorNumberInt = stoi(authorNumber);

    } while (!(0 <= authorNumberInt && authorNumberInt <= counterOfAuthors));
    return (authorNumberInt - 1);
}

void AuthorFunctions::AssignABookToAuthor()
{

    int authorNumberInt = getAuthorNumber();
    if (authorNumberInt == -1)
        return;

    authorCurrent = authorHead;
    for (int i = 0; i < authorNumberInt; i++)
    {
        authorCurrent = authorCurrent->nextAuthor;
    }

    system("cls");
    cout << "\n--------------------All Books-----------------------\n";

    bookCurrent = bookHead;
    int counterOfBooks = 0;
    for (int i = 0; bookCurrent != NULL; i++)
    {
        cout << i + 1 << ". Book Title: " << bookCurrent->title << endl;
        bookCurrent = bookCurrent->nextBook;
        counterOfBooks++;
    }
    string assigns;

    cout << "\n\nEnter Number of books you want to Assign ";
    int assignsInt;
    do
    {
        cin >> assigns;
        isNumber(&assigns);
        assignsInt = stoi(assigns);
    } while (!(0 <= assignsInt && assignsInt <= counterOfBooks));

    vector<string> Books(assignsInt);
    for (int i = 0; i < assignsInt; i++)
    {

        cout << "Choose Book Number ";
        cin >> Books[i];
        isNumber(&Books[i]);
        int BookNumber = stoi(Books[i]);
        BookNumber--;

        bookCurrent = bookHead;
        for (int i = 0; i < BookNumber; i++)
        {
            bookCurrent = bookCurrent->nextBook;
            if(bookCurrent == NULL){
                cout << "Invalid book number. Please try again." << endl;
                cin.ignore();
                cin.get();
                return;
            }
        }

        stack<string *> tempStack;
        while (!authorCurrent->authorBooksNames.empty())
        {
            if(authorCurrent->authorBooksNames.top() == &(bookCurrent->title)){
                cout << "This book is already assigned to this author\n";
                cout << "\nPress Enter to continue";
                while (!tempStack.empty()){
                    authorCurrent->authorBooksNames.push(tempStack.top());
                    tempStack.pop();
                }
                cin.ignore();
                cin.get();
                return;
            }
            tempStack.push(authorCurrent->authorBooksNames.top());
            authorCurrent->authorBooksNames.pop();
        }

        while (!tempStack.empty())
        {
            authorCurrent->authorBooksNames.push(tempStack.top());
            tempStack.pop();
        }

        authorCurrent->authorBooksNames.push(&(bookCurrent->title)); // Done

        bookCurrent->authorName = &authorCurrent->name;
    }
    cout << "\t\t\t\t Press Enter to continue  \n";
    cin.ignore();
    cin.get();
}

void AuthorFunctions::RemoveBooksFromAuthor()
{
    int authorNumberInt = getAuthorNumber();
    if (authorNumberInt == -1)
        return;

    // Search for the chosen author
    Author *authorToRemove = authorHead;
    for (int i = 0; i < authorNumberInt && authorToRemove != NULL; i++)
    {
        authorToRemove = authorToRemove->nextAuthor;
    }

    // Print the chosen author's books
    stack<string *> tempAuthorBooksNames = authorToRemove->authorBooksNames;
    for (int counter = 1; !tempAuthorBooksNames.empty(); counter++)
    {
        cout << counter << ". Book Title: " << *tempAuthorBooksNames.top() << endl;
        tempAuthorBooksNames.pop();
    }

    string isNumberValue;
    cout << "Enter the number of books you want to remove: ";
    cin >> isNumberValue;
    isNumber(&isNumberValue);
    int numBooksToRemove = stoi(isNumberValue);

    for (int i = 0; i < numBooksToRemove; i++)
    {
        cout << "Choose book number to remove: ";
        cin >> isNumberValue;
        isNumber(&isNumberValue);
        int bookNumber = stoi(isNumberValue);

        // remove the book from the Author
        if (bookNumber >= 1 && bookNumber <= authorToRemove->authorBooksNames.size())
        {
            // Create a temporary stack to hold the books
            stack<string *> tempStack;
            while (bookNumber > 1)
            {
                tempStack.push(authorToRemove->authorBooksNames.top());
                authorToRemove->authorBooksNames.pop();
                bookNumber--;
            }

            // remove the Author form the book
            bookCurrent = bookHead;
            while (bookCurrent->title != *authorToRemove->authorBooksNames.top()){
                bookCurrent = bookCurrent->nextBook;
            }
            bookCurrent->authorName = nullptr;

            // Pop the book to be removed
            authorToRemove->authorBooksNames.pop();

            // Push the remaining books back
            while (!tempStack.empty())
            {
                authorToRemove->authorBooksNames.push(tempStack.top());
                tempStack.pop();
            }

            cout << "Book removed successfully." << endl;
        }
        else
        {
            cout << "Invalid book number. Please try again." << endl;
        }
    }

    cout << "Press Enter to continue..." << endl;
    cin.ignore();
    cin.get();

    system("cls");
}

void AuthorFunctions::updateAuthor()
{
    int authorNumberInt = getAuthorNumber();
    if (authorNumberInt == -1)
        return;

    authorCurrent = authorHead;
    for (int i = 0; i < authorNumberInt; i++)
    {
        authorCurrent = authorCurrent->nextAuthor;
    }

    char Choice;
    do
    {
        system("cls");
        cout << "What do you  want to update" << endl;
        cout << "1- Author Name: " << endl;
        cout << "2- Exit: " << endl;
        cout << "Enter your choice: ";
        cin >> Choice;
        system("cls");

        string newId;
        string newName;
        switch (Choice)
        {
        case '1':
            cout << "Author Name: ";
            cin.ignore();
            getline(cin, newName);
            authorCurrent->name = newName;
            break;
        case '2':
            break;
        default:
            cout << "Invalid choice" << endl;
            break;
        }
    } while (Choice != '2');

    system("cls");
    cout << "\n\n\n\n\n\t\t\t\t Author Updated Successfully\n\n\t\t\t\tPress Enter to continue.";
    cin.ignore();
    cin.get();
}

void AuthorFunctions::RemoveAnAuthor()
{
    if (authorHead == NULL)
    {
        cout << "------------------- No Authors yet -------------------\n";
        cout << "\nPress Enter to continue";
        cin.ignore();
        cin.get();
        system("cls");
        return;
    }

    string authorNumber;
    cout << "\n--------------------All Authors-----------------------\n";

    authorCurrent = authorHead;
    for (int i = 0; authorCurrent != NULL; i++)
    {
        cout << i + 1 << ". Author Name: " << (authorCurrent->name) << endl;
        authorCurrent = authorCurrent->nextAuthor;
    }

    cout << "\n\nChoose an Author ";
    cin >> authorNumber;
    isNumber(&authorNumber);
    int authorNumberInt = stoi(authorNumber);
    authorNumberInt--;

    if (authorHead == authorTail)
    {

        delete authorHead;
        authorHead = NULL;
        authorTail = NULL;
    }
    else if (authorNumberInt == 0)
    {
        authorTemp = authorHead;
        authorHead = authorHead->nextAuthor;

        delete authorTemp;
    }
    else
    {
        authorCurrent = authorHead;
        for (int i = 0; i < authorNumberInt - 1; i++)
        {
            authorCurrent = authorCurrent->nextAuthor;
        }

        if (authorCurrent->nextAuthor == authorTail)
        {
            authorTemp = authorTail;
            authorTail = authorCurrent;
            authorTail->nextAuthor = NULL;

            delete authorTemp;
        }
        else
        {
            authorTemp = authorCurrent->nextAuthor;
            authorCurrent->nextAuthor = authorTemp->nextAuthor;

            delete authorTemp;
        }
    }
}

void AuthorFunctions::DeleteAllAuthors()
{
    cout << "If you want to delete all Author press 1, else Enter Anything else\n";
    char choice;
    cin >> choice;

    if (choice == '1')
    {
        authorCurrent = authorHead;
        for (int i = 0; authorCurrent != NULL; i++)
        {
            authorTemp = authorCurrent;
            authorCurrent = authorCurrent->nextAuthor;
            delete authorTemp;
        }
        authorHead = NULL;
        authorTail = NULL;

        cout << "\n\n\n\n\n\t\t\t\tAll Author Deleted Successfully\n";
        Sleep(2000);
        system("cls");
    }
    system("cls");
    cout << "\n\n\n\n\n\t\t\t\t All Authors Deleted Successfully\n\n\t\t\t\tPress Enter to continue.";
    cin.get();
}

#endif
