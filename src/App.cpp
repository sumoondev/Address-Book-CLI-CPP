#include <iostream>     // perform io operations
#include <cstdlib>      // for system() fn
#include <cstring>      // perform string operation
#include <chrono>       // for chrono::millisecond() fn
#include <thread>       // for this_thread::sleep_for() fn

using namespace std;

// Contact node for AVL Tree
class Contact {
    private:    
        string name;
        long mobile;
        string address;
        string email;
    public:
        Contact* left;
        Contact* right;
        static int count;       // stores count of contacts
        int height;             // for storing height of current node (for AVL implementation)

        Contact(string name, long mobile, string address, string email) {
            this->name = name;
            this->mobile = mobile;
            this->address = address;
            this->email = email;
            this->left = NULL;
            this->right = NULL;
            this->height = 1;
        }

        void display() {
            cout << "1. Full Name : " << this->name << endl;
            cout << "2. Mobile : " << this->mobile << endl;
            cout << "3. Address : " << this->address << endl;
            cout << "4. Email : " << this->email ;
        }

        void setMobile(long mobile) {
            this->mobile = mobile;
        }

        void setAddress(string address) {
            this->address = address;
        }

        void setEmail(string email) {
            this->email = email;
        }

        string getName() {
            return this->name;
        }
        
        long getMobile() {
            return this->mobile;
        }

        string getAddress() {
            return this->address;
        }

        string getEmail() {
            return this->email;
        }

        int compareTo(Contact c2) {
            return this->name.compare(c2.name);
        }

        int compareTo(string name) {
            return this->name.compare(name);
        }

        bool compareToUtil(string test) {
            return this->name.substr(0,test.length()).compare(test);
        }
};

// Object to store in JSON file
class DataContainer {
    public: 
        Contact* contact;
        int count;

        DataContainer(Contact* root, int count) {
            contact = root;
            this->count = count;
        }
};

// For performing vital operations like add contact, delete contact, etc;
class Service {
    private:
        static Contact* root;


};


// For performing utility operations like clear screen, load and save contact, etc.
class Utility {
    private:

    public: 
        static void clearScreen() {
            // Check the operating system
            #ifdef _WIN32
                system("cls"); // Clear screen for Windows
            #else
                system("clear"); // Clear screen for Unix/Linux/Mac
            #endif
        } 
        
        static void printInvalid() {

        }
};

// Main section that executes
int main() {

    return 0;
}