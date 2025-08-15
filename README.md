# Address-Book-CLI-CPP
A modular C++ based Address Book application designed to start with a Command-Line Interface (CLI). 
Provides core contact management features—CRUD operations, JSON persistence, search and validation.

---

## Table of Contents

* [Project Overview](#project-overview)
* [Features](#features)
* [Prerequisites](#prerequisites)
* [Getting Started](#getting-started)
  * [Clone & Build](#clone--build)
  * [Run](#run)
* [Usage Examples](#usage-examples)
* [Project Structure](#project-structure)
* [Configuration](#configuration)
* [Testing](#testing)
* [Contributing](#contributing)
* [License](#license)
* [Acknowledgments](#acknowledgments)

---

## Project Overview

This repository contains a single source file, **`App.cpp`**, which implements a console‑based Address Book. It uses a binary‑search tree (BST) for in‑memory contact storage and the [nlohmann/json](https://github.com/nlohmann/json) library for JSON persistence. User authentication, input validation, and animated console output are all contained within `App.cpp`.

---

## Features

* On startup, all profiles and existing contacts are loaded from **`addressbook.json`** (if present).
* User **Sign Up / Sign In** from loaded JSON file
* **Add / Update / Delete / Search / View All** contacts
* **BST‑backed** in‑memory data structure
* JSON-based persistence (load on startup, save on exit)
* Validation, duplicate detection, and basic search/filter capabilities
* Animated CLI with clear‑screen and typing effects

---

## Prerequisites

* A C++ compiler supporting **C++11** or later (e.g., `g++`, `clang++`, MSVC)
* The included **nlohmann/json** library (in `libs/json`)

---

## Getting Started

### Clone & Build

```bash
git clone https://github.com/sumoondev/Address-Book-CLI-CPP.git
cd Address-Book-CLI-CPP
```

#### Linux / macOS

```bash
g++ -std=c++11 -Ilibs/json/include src/App.cpp -o addressbook
```

#### Windows (MSVC)

```powershell
cl /EHsc /std:c++17 /I libs\json\include src/App.cpp /Fe:addressbook.exe
```

---

### Run

```bash
# On Linux / macOS
./addressbook

# On Windows
addressbook.exe
```

On first run, choose **Sign Up** to create an account. On subsequent runs, choose **Sign In** to load your contacts.

---

## Usage Examples

```bash
-- Main Page --
=== Address Book CLI by The G's ===
1) Create Profile
2) Login To Profile
3) List Profile
4) Delete Profile
5) Exit
Enter a choice : 

-- Sign Up --
=== Create Profile ===
Username    : Alice
Password    : *****
Re-password : *****
----------------------------------
User created

-- Sign In --
Username: Alice
Password: *****
Login successful! Loading your contacts...

-- After Login --
User : Alice
=== Address Book CLI ===
1) Add Contact
2) List All Contacts
3) Search Contacts
4) Edit Contact
5) Delete Contact
6) Log Out

Enter a choice : 

-- Add Contact --
Name    : Bob Smith
Mobile  : 1234567890
Address : 123 Maple Street
Email   : bob@example.com
Contact added!
Press Enter to continue…
```

---

### Project Structure

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

## Configuration

* **User files**: Each account’s data is stored in `addressbook.json` in the working directory.
* To modify storage behavior, edit the JSON handling in `App.cpp`.

---

## Testing

*(No automated tests provided. You may write your own by refactoring into smaller modules.)*

---

## Contributing

Contributions are welcome! Since all functionality resides in `App.cpp`, please keep changes well commented and minimal:

1. Fork the repository
2. Create a feature branch
3. Make and test your changes
4. Submit a Pull Request

---

## License

This module is distributed under the [Apache License](LICENSE).

---

## Acknowledgments

This project uses the [nlohmann/json](https://github.com/nlohmann/json) library for JSON handling, which is licensed under the MIT License. The original copyright notice is included in the `libs/json` directory.

---

— Built by **The G's** | © 2025
