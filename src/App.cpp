#include <iostream>     // perform io operations
#include <cstdlib>      // for system() fn
#include <cstring>      // perform string operation
#include <chrono>       // for chrono::millisecond() fn
#include <thread>       // for this_thread::sleep_for() fn
#include "../libs/json/include/json.hpp" // Adjust the path to include json.hpp

using json = nlohmann::json;

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
class Profile {
    private:
        string password;
    public: 
        string username;
        Contact* contact;
        int count;

        Profile() {
            contact = NULL;
            count = 0;
        }

        Profile(Contact* root, int count) {
            contact = root;
            this->count = count;
        }

        bool login(string pwd) {
            if(this->password.compare(pwd) == 0) {
                return true;
            }
            return false;
        }
};

// For performing utility operations like clear screen, load and save contact, etc.
class Utility {
    private:
        string FILE_PATH = "addressbook.json";
    public: 
        static void clearScreen() {
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
            this_thread::sleep_for(chrono::milliseconds(200));
            // cout << "\r" ;               // "\r" - takes the cursor to the beginning of the current line
            // for(int i = 0; i < print.length(); i++) {
            //     cout << " " << flush;
            //     this_thread::sleep_for(chrono::milliseconds(100));
            // }
        }

        static bool isNameValid(string name) {
            for(int i = 0; i < name.length(); i++) {
                if(name[i] != ' ' && (name[i] < 'a' || name[i] > 'z') && (name[i] < 'A' || name[i] > 'Z')) {
                    return false;
                }
            }
            return true;
        }

        static bool isEmailValid(string email) {
            string validate = "@gmail.com";
            if(email.length() <= validate.length()) {
                return false;
            }
            if(email.substr(email.length(), validate.length()).compare(validate) != 0) {
                return false;
            }
            return true;
        }
};

// For performing vital operations like add contact, delete contact, etc;
class Service {
    private: 
        Contact* root;

        void display(int t, string email = NULL, string address = NULL, long mobile = NULL, string name = NULL) {
            Utility::clearScreen();
            cout << "=== Add Contact ===\n";
            if(name.compare(NULL) == 0) {
                cout << "Full Name : " ;
                Utility::printWithAnimation("Name is not valid !!\tTry ");
                cout << t << " / 3";
                this_thread::sleep_for(chrono::milliseconds(500));
            }
            else if(mobile == NULL) {
                cout << "Full Name : " << name;
                cout << "Mobile : ";
                Utility::printWithAnimation("Number is not valid !!\tTry ");
                cout << t << " / 3";
                this_thread::sleep_for(chrono::milliseconds(500));
            }
            else if(address.compare(NULL) == 0) {
                cout << "Full Name : " << name;
                cout << "Mobile : " << mobile;
                cout << "Address : ";
                Utility::printWithAnimation("Address is not valid !!\tTry ");
                cout << t << " / 3";
                this_thread::sleep_for(chrono::milliseconds(500));
            }
            else if(email.compare(NULL) == 0) {
                cout << "Full Name : " << name;
                cout << "Mobile : " << mobile;
                cout << "Address : " << address;
                cout << "Email : ";
                Utility::printWithAnimation("Email is not valid !!\tTry ");
                cout << t << " / 3";
                this_thread::sleep_for(chrono::milliseconds(500));
            }
            Utility::clearScreen();
            cout << "=== Add Contact ===\n";
            if(name.compare(NULL) == 0) {
                cout << "Full Name : " ;
            }
            else if(mobile == NULL) {
                cout << "Full Name : " << name;
                cout << "Mobile : ";
            }
            else if(address.compare(NULL) == 0) {
                cout << "Full Name : " << name;
                cout << "Mobile : " << mobile;
                cout << "Address : ";
            }
            else if(email.compare(NULL) == 0) {
                cout << "Full Name : " << name;
                cout << "Mobile : " << mobile;
                cout << "Address : " << address;
                cout << "Email : ";
            }
        }
    public:
        Service(Contact* persons) {
            root = persons;
        }        

        void addContact() {
            string name, address = NULL, email;
            long mobile;
            int t = 1;

            Utility::clearScreen();
            cout << "=== Add Contact ===" << endl;
            cout << "Full Name : ";
            do {
                getline(cin, name);
                if(!Utility::isNameValid(name)) {
                    display(t++);
                }
            } while(Utility::isNameValid(name));
            t = 1;
        }
};

// print menu section
void menu(Contact* root) {
    Service serv = Service(root);
    char choice;
    bool loop = true;
    while(loop) {
        Utility::clearScreen();
        cout << "=== Address Book CLI ===" << endl;
        cout << "1) Add Contact\n2) List All Contacts\n3) Search Contacts\n4) Edit Contact\n5) Delete Contact\n6) Save\n7) Save & Exit\n8) Exit without saving" << endl;
        cout << "Enter a choice : ";
        cin >> choice;
        switch (choice)
        {
        case '1':
            // serv.addContact();
            break;
        case '2':
            
            break;
        case '3':
            
            break;
        case '4':

            break;
        case '5':
            
            break;
        case '6':
            
            break;
        case '7':

            break;
        case '8':
            loop = false;
            break;
        default:
            cout << "\x1b[A";           // move cursor up by one line
            cout << "Enter a choice : ";
            Utility::printWithAnimation("Invalid choice, please try again");
            break;
        }
    }
}

// Main section that executes
int main() {
    Profile prof[5];
    bool loop = true;
    char choice;
    while(loop) {
        Utility::clearScreen();
        cout << "=== Address Book CLI by The G's ===" << endl;
        cout << "1) Create Profile\n2) Login To Profile\n3) List Profile\n4) Merge Two Profile\n5) Exit\n";
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
                loop = false;
                break;
            default:
                cout << "\x1b[A";           // move cursor up by one line
                cout << "Enter a choice : ";
                Utility::printWithAnimation("Invalid choice, please try again");
                break;
        }
    }
    return 0;
}