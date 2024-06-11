/*
                                                      Book Publisher Management System
                                                                  Members
                                                    Mohammed Abdulbaqi     -   222453432
                                                    Hassan Alkhamis        -   222403905
                                                    Basel Ahmed            -   222453505
                                                    Abdulrahman alsarawi   -   222434678
*/

#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>
#include <windows.h>
#include "BookFunctions.h"
#include "AuthorFunctions.h"
#include "GlobalFunctions.h"
#include "BorrowingBook.h"
using namespace std;

void mainMenu()
{
    string choice;
    BookFunctions bookFunctions;
    AuthorFunctions authorFunctions;
    BorrowingFunctions borrowFunctions;

    system("cls");
    system("Color 0A"); 
    cout << "\n\n\n\n\n\t\t\t\t Welcome To Book Publisher Management System";
    cout << "\n\n\t\t\t\t\tPress Enter to continue."; 
    cin.get();
    do
    {
        system("cls");
        system("Color 07");
        cout << "1  . Show All Books.\n";
        cout << "2  . Show All Authors.\n";
        cout << "3  . Add new Book.\n";
        cout << "4  . Add new Author.\n";
        cout << "5  . Assign book to an author.\n";
        cout << "6  . Remove a Book from an author.\n";
        cout << "7  . Update A Book.\n";
        cout << "8  . Update An Author.\n";
        cout << "9  . Remove A Book.\n";
        cout << "10 . Remove An Author.\n";
        cout << "11 . Delete All Books.\n";
        cout << "12 . Delete All Authors.\n";
        cout << "13 . search for a book details.\n";
        cout << "14 . search for an Author details.\n";
        cout << "15 . Borrow a book.\n";
        cout << "16 . Show Borrowed book.\n";
        cout << "17 . Return a Borrowed book.\n";
        cout << "18 . Save.\n";
        cout << "19 . Save and Exit.\n";

        cout << "Enter your choice: ";
        cin >> choice;

        system("cls");
        if (choice == "1")
        {
            bookFunctions.showAllBooks();
        }
        else if (choice == "2")
        {
            authorFunctions.showAllAuthors();
        }
        else if (choice == "3")
        {
            bookFunctions.addBook();
        }
        else if (choice == "4")
        {
            authorFunctions.addAuthor();
        }
        else if (choice == "5")
        {
            authorFunctions.AssignABookToAuthor();
        }
        else if (choice == "6")
        {
            authorFunctions.RemoveBooksFromAuthor();
        }
        else if (choice == "7")
        {
            bookFunctions.updateBook();
        }
        else if (choice == "8")
        {
            authorFunctions.updateAuthor();
        }
        else if (choice == "9")
        {
            bookFunctions.RemoveABook();
        }
        else if (choice == "10")
        {
            authorFunctions.RemoveAnAuthor();
        }
        else if (choice == "11")
        {
            bookFunctions.DeleteAllBooks();
        }
        else if (choice == "12")
        {
            authorFunctions.DeleteAllAuthors();
        }
        else if (choice == "13")
        {
            searchForBook();
        }
        else if (choice == "14")
        {
            searchForAuthor();
        }
        else if (choice == "15")
        {
            borrowFunctions.BorrowBook();
        }
        else if (choice == "16")
        {
            borrowFunctions.ShowBorrowedBook();
        }
        else if (choice == "17")
        {
            borrowFunctions.RemoveBook();
        }
        else if (choice == "18")
        {
            saveChanges();
            cout << "\n\n\n\n\n\t\t\t\tSaving...\n\n\n\n\n";
            Sleep(1000);
            system("cls");
        }
        else if (choice == "19")
        {
            saveChanges();
            cout << "\n\n\n\n\n\t\t\t\tGoodbye!\n\n\n\n\n";
            Sleep(1000);
            system("cls");
        }
        else
        {
            cout << "\t\t\t\tinvalid input! \nPress Enter to continue  \n";
            cin.ignore();
            cin.get();
            system("cls");
        }
    } while (choice != "19");
}

int main()
{
    BorrowingFunctions borrowFunctions;

    loadAuthors();
    loadBooks();
    loadAuthorsBooks();
    borrowFunctions.loadBorrowedBooks();
    mainMenu();

    return 0;
}
