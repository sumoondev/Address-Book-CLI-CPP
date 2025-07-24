#include <iostream>
#include <cstdlib>

using namespace std;

void clearScreen() {
    // Check the operating system
    #ifdef _WIN32
        system("cls"); // Clear screen for Windows
    #else
        system("clear"); // Clear screen for Unix/Linux/Mac
    #endif
}
int main() {
    cout << "This is some text." << endl;
    cout << "Clearing the screen..." << endl;
    // Call the function to clear the screen
    clearScreen();
    cout << "The screen has been cleared!" << endl;
    cin;
    return 0;
}