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

void printWithAnimation(string print) {
    for(int i = 0; i < print.length(); i++) {
                cout << print[i] << flush;
                this_thread::sleep_for(chrono::milliseconds(100));
            }
            this_thread::sleep_for(chrono::milliseconds(200));
            cout << "\r" << flush;
            for(int i = 0; i < print.length(); i++) {
                cout << " " << flush;
                this_thread::sleep_for(chrono::milliseconds(100));
            }
        }
int main() {
    // cout << "This is some text." << endl;
    // cout << "Clearing the screen..." << endl;
    // // Call the function to clear the screen
    // clearScreen();
    // cout << "The screen has been cleared!" << endl;
    // string getc;
    // cin >> getc;

    printWithAnimation("I n v a l i d  ! ! !");
    
    return 0;
}