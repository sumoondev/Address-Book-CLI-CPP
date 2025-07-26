# Address-Book-CLI-CPP
A modular C++ based Address Book application designed to start with a Command-Line Interface (CLI). 
Provides core contact management features—CRUD operations, JSON persistence, search and validation.

---

### Repository Structure

```
Address-Book-CLI-CPP/                 ← Top-level repository
├── README.md                         ← Overview, usage, and module guide
├── .gitignore                        ← Files and folders to ignore in Git
├── LICENSE
│── target/                           ← Output: compiled objects (`.obj`), etc.
│── src/                              ← Contains all the source code
│── libs/                             ← Consists all the third party libraries 
│── test/                             
└── addressbook.json                  ← Default JSON persistence file

```

---

### Project Overview

This project Address Book application implements:
  - Create, Read, Update, Delete (CRUD) of contacts
  - Stores data like name, address, phone numbers, and emails
  - JSON-based persistence (load on startup, save on exit)
  - Validation, duplicate detection, and basic search/filter capabilities

---

### Getting Started 

1. **Clone the repository**
   ```bash
   git clone https://github.com/PhantomBenz/Address-Book-CLI-CPP.git
   cd Address-Book-CLI-CPP/
   ```

2. **Build and Run**

    * **Required Dependencies**
      - C/C++ 
      - C/C++ Extension Pack
      *Note: For Visual Studio Code*

   * **For Windows**:

     ```bash

     ```
   
   * **For Linux/Mac**:

     ```bash
      
     ```

3. **Usage**

   * On startup, existing contacts are loaded from `addressbook.json` (if present).
   * Follow the on-screen menu to add, list, search, edit, or delete contacts.
   * On exit, all changes are saved back to `addressbook.json`.

---

## Usage Examples

```
=== Address Book CLI ===

1) Add Contact
2) List All Contacts
3) Search Contacts
4) Edit Contact
5) Delete Contact
0) Exit
Enter choice: 
```

---

## License

This module is distributed under the [Apache License](LICENSE).

---

## Acknowledgments

This project uses the [nlohmann/json](https://github.com/nlohmann/json) library for JSON handling, which is licensed under the MIT License. The original copyright notice is included in the `libs/json` directory.

---

— Built by **The G's** | © 2025