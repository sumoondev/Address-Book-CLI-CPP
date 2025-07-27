#include <iostream>     // perform io operations
#include <cstdlib>      // for system() fn
#include <cstring>      // perform string operation
#include <chrono>       // for chrono::millisecond() fn
#include <thread>       // for this_thread::sleep_for() fn
#include <fstream>      // for file handling
#include <limits>
#include <memory>
#include <vector>

#include "../libs/json/include/nlohmann/json.hpp"

using json = nlohmann::json;

using namespace std;

// Contact node for AVL Tree
class Contact {
    private:    
        string name;
        string mobile;
        string address;
        string email;
    public:
        Contact* left;
        Contact* right;
        int height;             // for storing height of current node (for AVL implementation)

        Contact(string name, string mobile, string address, string email) {
            this->name = name;
            this->mobile = mobile;
            this->address = address;
            this->email = email;
            this->left = NULL;
            this->right = NULL;
            this->height = 1;
        }

        // ~Contact() {
        //     delete left;
        //     delete right;
        // }

        void display() {
            cout << "1. Full Name : " << this->name << endl;
            cout << "2. Mobile : " << this->mobile << endl;
            cout << "3. Address : " << this->address << endl;
            cout << "4. Email : " << this->email << endl ;
        }

        void setMobile(string mobile) {
            this->mobile = mobile;
        }

        void setAddress(string address) {
            this->address = address;
        }

        void setEmail(string email) {
            this->email = email;
        }

        void setData(Contact* temp) {
            this->name = temp->name;
            this->mobile = temp->mobile;
            this->address = temp->address;
            this->email = temp->email;
        }

        string getName() {
            return this->name;
        }
        
        string getMobile() {
            return this->mobile;
        }

        string getAddress() {
            return this->address;
        }

        string getEmail() {
            return this->email;
        }

        int compareTo(Contact* c2) const {
            return this->name.compare(c2->name);
        }

        int compareTo(string name) const {
            return this->name.compare(name);
        }

        bool compareToUtil(string test) {
            if (test.length() > this->name.length()) {
                return false;
            }
            return this->name.substr(0, test.length()).compare(test) == 0;
        }

        // Serialize a contact (including subtree)
        static json serialize(Contact* node) {
            if (!node) {
                return nullptr;
            }

            json j;
            j["name"] = node->name;
            j["mobile"] = node->mobile;
            j["address"] = node->address;
            j["email"] = node->email;
            j["height"] = node->height;
            j["left"] = serialize(node->left);
            j["right"] = serialize(node->right);
            
            return j;
        }

        // Deserialize a contact (including subtree)
        static Contact* deserialize(const json& j) {
            if (j.is_null()) {
                return nullptr;
            }

            Contact* node = new Contact(
                j["name"].get<string>(),
                j["mobile"].get<string>(),
                j["address"].get<string>(),
                j["email"].get<string>()
            );
            node->height = j["height"].get<int>();
            node->left = deserialize(j["left"]);
            node->right = deserialize(j["right"]);
            
            return node;
        }
};

// For multiple Profile and saving in JSON file
class Profile {
    public: 
        string username;
        string password;
        Contact* contact; // root of AVL tree

        Profile() {
            contact = NULL;
        }

        // Creating new Profile
        Profile(string username, string pwd) {
            this->username = username;
            this->password = pwd;
            this->contact = NULL;
        }

        // For JSON file reading 
        Profile(string username, string pwd, Contact* root) { 
            this->username = username;
            this->password = pwd;
            contact = root;
        }

        ~Profile() {
            delete contact;
        }

        bool login(string pwd) const {
            if(this->password.compare(pwd) == 0) {
                return true;
            }
            return false;
        }

        void to_json(json& j) const {
            j = {
                {"username", username},
                {"password", password},
                {"contact", Contact::serialize(contact)}
            };
        }

        void from_json(const json& j) {
            username = j["username"];
            password = j["password"];
            // Existing contact tree is deleted
            if (contact) {
                delete contact;
                contact = nullptr;
            }
            // deserializing a new Contact
            contact = Contact::deserialize(j["contact"]);
        }
};

// For performing utility operations like clear screen, load and save contact, etc.
class Utility {
    private:
        string FILE_PATH = "../../addressbook.json";
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
                this_thread::sleep_for(chrono::milliseconds(50));
            }
            this_thread::sleep_for(chrono::milliseconds(200));
            cout << endl;
        }

        static bool isNameValid(const string& name) {
            if (name.empty()) {
                return false;
            }
            for(int i = 0; i < name.length(); i++) {
                if(isalpha(name[i]) || isspace(name[i])){ 
                    return true;
                }
            }
            return false;
        }

        bool isEmailValid(string email) {
            string validate = "@gmail.com";
            if(email.length() <= validate.length()) {
                return false;
            }
            if(email.substr(email.length() - validate.length()).compare(validate) != 0) {
                return false;
            }
            return true;
        }

        static bool isMobileValid(string mobile) {
            if(mobile.length() != 10) {
                return false;
            }
            for(int i = 0; i < 10; i++) {
                if(!isdigit(mobile[i])) {
                    return false;
                }
            }
            return true;
        }

        // Save entire profile array to json
        void saveProfiles(const vector<Profile*>& profiles) {
            json j_array = json::array();
            
            for (const auto& profile_ptr : profiles) {
                if (profile_ptr) { // Ensure the pointer is not null
                    json j_profile;
                    profile_ptr->to_json(j_profile);
                    j_array.push_back(j_profile);
                }
            }
            
            ofstream ofs(FILE_PATH);
            if (!ofs.is_open()) {
                cerr << "Error: Could not open file for writing: " << FILE_PATH << endl;
                return;
            }
            ofs << j_array.dump(4);  // Pretty print with indentation
            ofs.close();
        }

        // Load profiles from JSON
        void loadProfiles(vector<Profile*>& profiles) {
            ifstream ifs(FILE_PATH);
            if (!ifs.is_open()) {
                cout << "File not found or error opening file: " << FILE_PATH << ". Starting with no profiles." << endl;
                profiles.clear(); // Ensure vector is empty if file doesn't exist
                return;
            }
            
            // Check if the file is empty
            if (ifs.peek() == ifstream::traits_type::eof()) {
                cout << "File is empty, no profiles to load." << endl;
                profiles.clear();
                ifs.close();
                return;
            }

            json j_array;
            try {
                ifs >> j_array;
            } catch (const json::parse_error& e) {
                cerr << "JSON parse error: " << e.what() << endl;
                cout << "Corrupted file, starting with no profiles." << endl;
                profiles.clear();
                ifs.close();
                return;
            }
            ifs.close();

            profiles.clear(); // Clear existing profiles before loading new ones
            for (const auto& j_profile : j_array) {
                Profile* new_profile = new Profile(); // Create a new Profile object
                try {
                    new_profile->from_json(j_profile);
                    profiles.push_back(new_profile);
                } catch (const json::exception& e) {
                    cerr << "Error deserializing profile: " << e.what() << ". Skipping this profile." << endl;
                    delete new_profile; // Clean up if deserialization fails
                }
            }
            cout << profiles.size() << " profiles loaded." << endl;
        }

        static bool isUsernameOrPasswordValid(string usrpwd) {
            if (usrpwd.empty()) {
                return false;
            }
            for(int i = 0; i < usrpwd.length(); i++) {
                if(isspace(usrpwd[i])) {
                    return false;
                }
            }
            return true;
        }
        
        static bool doesUsernameExists(string usrname, const vector<Profile*>& profiles) {
            for(const auto& profile_ptr : profiles) {
                if (profile_ptr && profile_ptr->username.compare(usrname) == 0) {
                    return true;
                }
            }
            return false;
        }

        static void printLine() {
            cout << "----------------------------------" << endl;
        }

        static void printStar(string word) {
            for(int i = 0; i < word.length(); i++) {
                cout << "*";
            }
            cout << endl;
        }

        static void printSpace() {
            for(int i = 0; i < 30; i++) {
                cout << " ";
            }
            cout << endl;
        }

        int getProfileIndex(const vector<Profile*>& profiles, string username) {
            for(size_t i = 0; i < profiles.size(); ++i) {
                if(profiles[i] && profiles[i]->username.compare(username) == 0) {
                    return static_cast<int>(i);
                }
            }
            return -1;
        }

        void listProfile(const vector<Profile*>& profiles) {
            if (profiles.empty()) {
                cout << "No profiles available." << endl;
                return;
            }
            for(size_t i = 0; i < profiles.size(); ++i) {
                if (profiles[i]) {
                    cout << i+1 << ". " << profiles[i]->username << endl; 
                }
            }
        }

        static void pressEnterToContinue() {
            string s;
            cout << "Press Enter to continue ...";
            getline(cin,s);
        }
};

// For performing vital operations like add contact, delete contact, etc;
class Service {
    private: 
        Utility util;
        Contact* &root;

        void display(int t, string name = "", string mobile = "", string address = "", string email = "") {             // t - attempt
            Utility::clearScreen();
            cout << "=== Add Contact ===\n";
            if(name.empty()) {
                cout << "Full Name : " ;
                Utility::printWithAnimation("Name is not valid !!\tTry ");
                cout << t << " / 3";
                this_thread::sleep_for(chrono::milliseconds(500));
            }
            else if(mobile.empty()) {
                cout << "Full Name : " << name << endl;
                cout << "Mobile    : ";
                Utility::printWithAnimation("Number is not valid !!\tTry ");
                cout << t << " / 3";
                this_thread::sleep_for(chrono::milliseconds(500));
            }
            else if(address.empty()) {
                cout << "Full Name : " << name << endl;
                cout << "Mobile    : " << mobile << endl;
                cout << "Address   : ";
                Utility::printWithAnimation("Address is not valid !!\tTry ");
                cout << t << " / 3";
                this_thread::sleep_for(chrono::milliseconds(500));
            }
            else if(email.empty()) {
                cout << "Full Name : " << name << endl;
                cout << "Mobile    : " << mobile << endl;
                cout << "Address   : " << address << endl;
                cout << "Email     : ";
                Utility::printWithAnimation("Email is not valid !!\tTry ");
                cout << t << " / 3";
                this_thread::sleep_for(chrono::milliseconds(500));
            }
            Utility::clearScreen();
            cout << "=== Add Contact ===\n";
            if(name.compare("") == 0) {
                cout << "Full Name : " ;
            }
            else if(mobile.empty()) {
                cout << "Full Name : " << name << endl;
                cout << "Mobile    : ";
            }
            else if(address.empty()) {
                cout << "Full Name : " << name << endl;
                cout << "Mobile    : " << mobile << endl;
                cout << "Address   : ";
            }
            else if(email.empty()) {
                cout << "Full Name : " << name << endl;
                cout << "Mobile    : " << mobile << endl;
                cout << "Address   : " << address << endl;
                cout << "Email     : ";
            }
        }
    
        int height(Contact* curr) {
            if(curr == NULL) {
                return 0;
            }
            return curr->height;
        }

        Contact* rightRotate(Contact* critNode) {
            Contact* x = critNode->left;
            Contact* y =  x->right;

            x->right = critNode;
            critNode->left = y;

            critNode->height = (height(critNode->left) > height(critNode->right) ? height(critNode->left) : height(critNode->right)) + 1;

            x->height = (height(x->left) > height(x->right) ? height(x->left) : height(x->right)) + 1;

            return x;
        }

        Contact* leftRotate(Contact* critNode) {
            Contact* y = critNode->right;
            Contact* x =  y->left;

            y->left = critNode;
            critNode->right = x;

            critNode->height = (height(critNode->left) > height(critNode->right) ? height(critNode->left) : height(critNode->right)) + 1;

            y->height = (height(y->left) > height(y->right) ? height(y->left) : height(y->right)) + 1;

            return x;
        }

        int getBalance(Contact* curr) {
            if(curr == NULL) {
                return 0;
            }
            return height(curr->left) - height(curr->right);
        }

        Contact* addContactUtil(Contact* current, Contact* newContact) {
            if(current == NULL) {
                return newContact;
            }
            if(current->compareTo(newContact) > 0) {
                current->left = addContactUtil(current->left, newContact);
            }
            else if(current->compareTo(newContact) < 0) {
                current->right = addContactUtil(current->right, newContact);
            }
            else {
                delete newContact;
                return current;
            }

            current->height = (height(current->left) > height(current->right) ? height(current->left) : height(current->right)) + 1;

            int bf = getBalance(current);

            if(bf > 1 && current->left->compareTo(newContact) > 0) {
                return rightRotate(current);
            }

            if(bf < -1 && current->right->compareTo(newContact) < 0) {
                return leftRotate(current);
            }

            if(bf > 1 && current->left->compareTo(newContact) < 0) {
                current->left = leftRotate(current->left);
                return rightRotate(current);
            }

            if(bf < -1 && current->right->compareTo(newContact) > 0) {
                current->right = rightRotate(current->right);
                return leftRotate(current);
            }

            return current;
        }

        Contact* searchContactUtil(Contact* current, string newName) {
            if(current == NULL) {
                return NULL;
            }
            if(current->compareTo(newName) == 0) {
                return current;
            }
            if(current->compareTo(newName) < 0) {
                return searchContactUtil(current->right, newName);
            }
            else{
                return searchContactUtil(current->left, newName);
            }
        }

        void searchContactUtilA(Contact* current, string search) {
            if(current == NULL) {
                return;
            }
            searchContactUtilA(current->left, search);
            if(current->compareToUtil(search)) {
                current->display();
                Utility::printLine();
            }
            searchContactUtilA(current->right, search);
        }

        void listContactUtil(Contact* current) {
            if(current == NULL) {
                return;
            }
            listContactUtil(current->left);
            current->display();
            Utility::printLine();
            listContactUtil(current->right);
        }

        Contact* getMinContact(Contact* current) {
            Contact* ptr = current;

            while(ptr->left != NULL) {
                ptr = ptr->left;
            }
            return ptr;
        }

        Contact* deleteContactUtil(Contact* curr, Contact* del) {
            if(curr->compareTo(del) > 0) {
                curr->left = deleteContactUtil(curr->left, del);
            }
            else if(curr->compareTo(del) < 0) {
                curr->right = deleteContactUtil(curr->right, del);
            }
            else {
                if(curr->left == NULL || curr->right == NULL) {
                    Contact* temp = NULL;
                    if(temp == curr->left) {
                        temp = curr->right;
                    } else {
                        temp = curr->left;
                    }
                    if(temp == NULL) {
                        temp = curr;
                        curr = NULL;
                    } else {
                        *curr = *temp;
                    }
                } else {
                    Contact* temp = getMinContact(curr->right);

                    curr->setData(temp);

                    curr->right = deleteContactUtil(curr->right, temp);
                }
            }

            if(curr == NULL) {
                return curr;
            }

            curr->height = (height(curr->left) > height(curr->right) ? height(curr->left) : height(curr->right)) + 1;

            int bf = getBalance(curr);

            if(bf > 1 && getBalance(curr->left) >= 0) {
                return rightRotate(curr);
            }

            if(bf > 1 && getBalance(curr->left) < 0) {
                curr->left = leftRotate(curr->left);
                return rightRotate(curr);
            }

            if(bf < -1 && getBalance(curr->right) <= 0) {
                return leftRotate(curr);
            }

            if(bf < -1 && getBalance(curr->right) > 0) {
                curr->right = rightRotate(curr->right);
                return leftRotate(curr);
            }

            return curr;
        }

        void editContactUtil(Contact* &curr) {
            Utility::clearScreen();
            cout << "=== Edit Contact ===";
            curr->display();
            cout << "\nWhat to Edit(eg : 1, 2, 3, 4, 5) : ";
            char choice;
            cin >> choice;
            string name, address, mobile, email;
            switch(choice) {
                case '1':
                    Utility::clearScreen();
                    cout << "Mobile : " << curr->getMobile() << endl;
                    cout << "Email : " << curr->getEmail() << endl;
                    cout << "Address : " << curr->getAddress() << endl;
                    cout << "Full Name : ";
                    getline(cin, name);
                    if(!Utility::isNameValid(name)) {
                        cout << "Name Invalid!!!\nName Unchanged" << endl;
                    } else {
                        Contact* newContact = new Contact(name, curr->getMobile(), curr->getAddress(), curr->getEmail());
                        root = deleteContactUtil(root, curr);
                        addContactUtil(root, newContact);
                        Utility::clearScreen();
                        cout << "=== Updated Contact ===" << endl;
                        newContact->display();
                    }
                    Utility::pressEnterToContinue();
                    break;
                case '2':
                    Utility::clearScreen();
                    cout << "Full Name : " << curr->getName() << endl;
                    cout << "Address : " << curr->getAddress() << endl;
                    cout << "Email : " << curr->getEmail() << endl;
                    cout << "Mobile: ";
                    getline(cin, mobile);
                    if(!Utility::isMobileValid(mobile)) {
                        cout << "Mobile number invalid!!!\nMobile number Unchanged" << endl;
                    } else {
                        curr->setMobile(mobile);
                        Utility::clearScreen();
                        cout << "=== Updated Contact ===" << endl;
                        curr->display();
                    }
                    Utility::pressEnterToContinue();
                    break;
                case '3':
                    Utility::clearScreen();
                    cout << "Full Name : " << curr->getName() << endl;
                    cout << "Mobile : " << curr->getMobile() << endl;
                    cout << "Email : " << curr->getEmail() << endl;
                    cout << "Address : ";
                    if(address.compare("") == 0) {
                        cout << "Address empty invalid!!!\nAddress Unchanged";
                    } else {
                        curr->setAddress(address);
                        Utility::clearScreen();
                        cout << "=== Updated Contact ===" << endl;
                        curr->display();
                    }
                    Utility::pressEnterToContinue();
                    break;
                case '4':
                    Utility::clearScreen();
                    cout << "Full Name : " << curr->getName() << endl;
                    cout << "Mobile : " << curr->getMobile() << endl;
                    cout << "Address : " << curr->getAddress() << endl;
                    cout << "Email : ";
                    getline(cin, email);
                    if(!util.isEmailValid(email)) {
                        cout << "Email invalid!!!\nEmail Unchanged";
                    } else {
                        curr->setEmail(email);
                        Utility::clearScreen();
                        cout << "=== Updated Contact ===" << endl;
                        curr->display();
                    }
                    Utility::pressEnterToContinue();
                    break;
                default:
                    Utility::clearScreen();
                    curr->display();
                    cout << "\nWhat to Edit(eg : 1, 2, 3, 4, 5) : ";
                    Utility::printWithAnimation("Choice Invalid");
                    Utility::pressEnterToContinue();
                    Utility::clearScreen();
            }
        }

        public:

        Service(Contact*& persons) : root(persons) {}     

        void addContact() {
            string name, address, email, mobile;
            int t = 1;
            const int MAX_ATTEMPTS = 3;

            Utility::clearScreen();
            cout << "=== Add Contact ===" << endl;
            cout << "Full Name : ";
            // cin.clear();
            // cin.ignore(numeric_limits<streamsize>::max(), '\n');
            do {
                getline(cin, name);
                if(!Utility::isNameValid(name)) {
                    display(t++);
                    if (t > MAX_ATTEMPTS) {
                        cout << "Too many invalid attempts. Returning to menu." << endl;
                        return;
                    }
                } else {
                    break;
                }
            } while(true);
            t = 1;

            Contact* exists = searchContactUtil(root, name);

            if(exists != NULL) {
                Utility::clearScreen();
                exists->display();
            }

            cout << "Mobile    : ";
            do {
                getline(cin, mobile);
                if(!Utility::isMobileValid(mobile)) {
                    display(t++,name);
                    if (t > MAX_ATTEMPTS) {
                        cout << "Too many invalid attempts. Returning to menu." << endl;
                        return;
                    }
                } else {
                    break;
                }
            } while(true);
            t = 1;
            
            cout << "Address   : ";
            do {
                getline(cin, address);
                if(address.empty()) {
                    display(t++,name, mobile);
                    if (t > MAX_ATTEMPTS) {
                        cout << "Too many invalid attempts. Returning to menu." << endl;
                        return;
                    }
                } else {
                    break;
                }
            } while(true);
            t = 1;

            cout << "Email     : ";
            do {
                getline(cin, email);
                if(!util.isEmailValid(email)) {
                    display(t++,name, mobile, address);
                    if (t > MAX_ATTEMPTS) {
                        cout << "Too many invalid attempts. Returning to menu." << endl;
                        return;
                    }
                } else {
                    break;
                }
            } while(true);

            Contact* newC = new Contact(name, mobile, address, email);
            root = addContactUtil(root, newC);
            Utility::printLine();
            Utility::printWithAnimation("=== New Contact Added ===");
            Utility::pressEnterToContinue();
        }

        void searchContact() {
            Utility::clearScreen();
            cout << "=== Search Contact ===\n";

            cout << "Enter Full or Partial name : ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            string name;
            getline(cin, name);
            Utility::clearScreen();
            cout << "=== Searched Contact ===\n";
            searchContactUtilA(root, name);
            Utility::pressEnterToContinue();
        }
        
        void listContact() {
            Utility::clearScreen();
            cout << "=== List of Contact ===\n";
            if (root == NULL) {
                cout << "No contacts available." << endl;
            } else {
                listContactUtil(root);
            }
            Utility::pressEnterToContinue();
            
        }

        void editContact() {
            Utility::clearScreen();
            cout << "=== Edit Contact ===" << endl;
            cout << "Enter Full Name: ";
            string name;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, name);

            Contact* ptr = searchContactUtil(root, name);
            if(ptr != NULL) {
                editContactUtil(ptr);
                return;
            }
            cout << name << " doesnot exist" << endl;
            Utility::pressEnterToContinue();
        }

        void deleteContact() {
            Utility::clearScreen();
            cout << "=== Delete Contact ===" << endl;
            cout << "Enter Full Name : ";
            string name;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, name);
            Contact* ptr = searchContactUtil(root, name);
            if(ptr != NULL) {
                deleteContactUtil(root, ptr);
                return;
            }
            cout << name << " doesnot exist" << endl;
            Utility::pressEnterToContinue();
        }
        
        Contact* getRoot() const { 
            return root; 
        }

};

// print menu section
void menu(Profile* current) {
    Service serv = Service(current->contact);
    char choice;
    bool loop = true;
    while(loop) {
        Utility::clearScreen();
        cout << "User : " << current->username << endl;
        cout << "=== Address Book CLI ===" << endl;
        cout << "1) Add Contact\n2) List All Contacts\n3) Search Contacts\n4) Edit Contact\n5) Delete Contact\n6) Log Out\n" << endl;
        cout << "Enter a choice : ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        switch (choice)
        {
            case '1':
                serv.addContact();
                break;
            case '2':
                serv.listContact();
                break;
            case '3':
                serv.searchContact();
                break;
            case '4':
                serv.editContact();
                break;
            case '5':
                serv.deleteContact();
                break;
            case '6':
                loop = false;
                Utility::printLine();
                Utility::printWithAnimation("Logging out...");
                break;
            default:
                cout << "\x1b[A";           // move cursor up by one line
                cout << "Enter a choice : ";
                Utility::printWithAnimation("Invalid choice, please try again");
                break;
        }
    }
    Utility::pressEnterToContinue();
}

// Main section that executes
int main() {
    Utility util;
    // Use std::vector for dynamic management of profiles
    vector<Profile*> profiles; 
    const int MAX_PROFILES = 10; // Define a reasonable max for the vector if needed, though vector handles growth

    util.loadProfiles(profiles);
    bool loop = true;
    char choice;
    string usrname, password, repwd;
    Profile* current_profile; 
    int curr;
    while(loop) {
        Utility::clearScreen();
        cout << "=== Address Book CLI by The G's ===" << endl;
        cout << "1) Create Profile\n2) Login To Profile\n3) List Profile\n4) Merge Two Profile\n5) Exit\n";
        cout << "Enter a choice : ";
        cin >> choice;
        // Ignore the newline character left in the input buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch (choice)
        {
            case '1':
                Utility::clearScreen();
                cout << "=== Create Profile ===" << endl;
                cout << "Username    : ";
                
                getline(cin,usrname);
                if(!Utility::isUsernameOrPasswordValid(usrname) || usrname.empty()) {
                    cout << "\x1b[A";
                    Utility::printSpace();
                    cout << "\x1b[A";
                    cout << "\rUsername    : ";
                    Utility::printWithAnimation("Username not accepted !!!");
                    break;
                }
                else if(Utility::doesUsernameExists(usrname, profiles)) {
                    Utility::clearScreen();
                    cout << "=== Create Profile ===" << endl;
                    cout << "Username    : ";
                    Utility::printWithAnimation("Username already taken !!!");
                    break;
                }
                cout << "Password    : ";
                
                getline(cin,password);
                if(!Utility::isUsernameOrPasswordValid(password)) {
                    cout << "\x1b[A";
                    Utility::printSpace();
                    cout << "Password    : ";
                    Utility::printWithAnimation("Password not accepted !!!");
                }
                cout << "\x1b[A";           // move cursor up by one line
                cout << "Password    : " ;
                Utility::printStar(password);
                cout << "Re-password : ";
                getline(cin,repwd);
                if(password.compare(repwd) != 0) {
                    cout << "\x1b[A";           // move cursor up by one line
                    Utility::printSpace();
                    cout << "\x1b[A";  
                    cout << "Re-password : ";
                    Utility::printWithAnimation("Password does not match !!!");
                    break;
                }
                cout << "\x1b[A";           // move cursor up by one line
                cout << "Re-password : " ;
                Utility::printStar(password);
                Utility::printLine();
                Utility::printWithAnimation(". . .");
                cout << "\x1b[A";           // move cursor up by one line
                cout << "       \r";
                // Add new profile to the vector
                profiles.push_back(new Profile(usrname, password));
                Utility::printWithAnimation("User created");
                Utility::pressEnterToContinue();
                break;
            case '2':
                Utility::clearScreen();
                cout << "=== Login Profile ===" << endl;
                cout << "Username : ";
                getline(cin, usrname);
                curr = util.getProfileIndex(profiles, usrname);
                if(curr == -1) {
                    cout << "\x1b[A";
                    Utility::printSpace();
                    cout << "\x1b[A" << "Username : ";
                    Utility::printWithAnimation("User not found");
                    break;
                }
                cout << "Password : ";
                // cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, password);
                current_profile = profiles[curr];
                if(!current_profile->login(password)) {
                    cout << "\x1b[A";
                    Utility::printSpace();
                    cout << "\rPassword : ";
                    Utility::printWithAnimation("Password incorrect");
                    break;
                }
                menu(current_profile);
                break;
            case '3':
                Utility::clearScreen();
                cout << "=== List of Contact ===" << endl;
                util.listProfile(profiles);
                Utility::printLine();
                Utility::pressEnterToContinue();
                break;
            case '4':
                // Merge code 
                break;
            case '5':
                loop = false;
                util.saveProfiles(profiles);
                break;
            default:
                cout << "\x1b[A";           // move cursor up by one line
                cout << "Enter a choice : ";
                Utility::printWithAnimation("Invalid choice, please try again");
                break;
        }
    }
    Utility::clearScreen();
    Utility::printWithAnimation("E x i t i n g  . . .");
    return 0;
}