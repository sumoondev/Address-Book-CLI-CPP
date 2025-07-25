#include <iostream>
#include <cstdlib>
#include <cstring>
#include <chrono>
#include <thread>

using namespace std;

void clearScreen() {
    // Check the operating system
    #ifdef _WIN32
        system("cls"); // Clear screen for Windows
    #else
        system("clear"); // Clear screen for Unix/Linux/Mac
    #endif
}

static void printWithAnimation(string print) {
            for(int i = 0; i < print.length(); i++) {
                cout << print[i] << flush;
                this_thread::sleep_for(chrono::milliseconds(100));
            }
            this_thread::sleep_for(chrono::milliseconds(500));
            // cout << "\r" << flush;
            // for(int i = 0; i < print.length(); i++) {
            //     cout << " " << flush;
            //     this_thread::sleep_for(chrono::milliseconds(100));
            // }
        }
int main() {
    // cout << "This is some text." << endl;
    // cout << "Clearing the screen..." << endl;
    // // Call the function to clear the screen
    // clearScreen();
    // cout << "The screen has been cleared!" << endl;
    // string getc;
    // cin >> getc;

    // printWithAnimation("I n v a l i d  ! ! !");
    
    char choice;
    bool loop = true;
    while(loop) {
        clearScreen();
        cout << "=== Address Book CLI ===" << endl;
        cout << "1) Add Contact\n2) List All Contacts\n3) Search Contacts\n4) Edit Contact\n5) Delete Contact\n0) Exit" << endl;
        cout << "Enter a choice : ";
        cin >> choice;
        switch (choice)
        {
        case '1':
            
            break;
        case '2':
            
            break;
        case '3':
            
            break;
        case '4':

            break;
        case '5':
            
            break;
        case '0':
            loop = false;
            break;
        default:
            cout << "\x1b[A"; 
            cout << "Enter a choice : ";
            printWithAnimation("Invalid choice, please try again!!!");
            break;
        }
    }

    return 0;
}