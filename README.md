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

* User **Sign Up / Sign In** with per‑user JSON sessions
* **Add / Update / Delete / Search / View All** contacts
* **BST‑backed** in‑memory data structure
* **JSON** file persistence (`<username>.json`)
* Animated CLI with clear‑screen and typing effects

---

## Prerequisites

* A C++ compiler supporting **C++11** or later (e.g., `g++`, `clang++`, MSVC)
* The included **nlohmann/json** library (in `libs/json`)

---

## Getting Started

### Clone & Build

```bash
git clone https://github.com/PhantomBenz/Address-Book-CLI-CPP.git
cd Address-Book-CLI-CPP
```

#### Linux / macOS

```bash
g++ -std=c++11 -Ilibs/json/include App.cpp -o addressbook
```

#### Windows (MSVC)

```powershell
cl /EHsc /std:c++17 /I libs\json\include App.cpp /Fe:addressbook.exe
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
$ ./addressbook
Welcome to Address Book CLI!
[1] Sign In
[2] Sign Up
Choice: 2

-- Sign Up --
Enter new username: alice
Enter new password: *****
Account created! Please sign in.

[1] Sign In
[2] Sign Up
Choice: 1

-- Sign In --
Username: alice
Password: *****
Login successful! Loading your contacts...

Main Menu:
1. Add Contact
2. Update Contact
3. Delete Contact
4. Search Contact
5. View All Contacts
6. Save & Exit
Choice: 1

-- Add Contact --
Name    : Bob Smith
Mobile  : 1234567890
Email   : bob@example.com
Address : 123 Maple Street
Contact added!
Press Enter to continue…
```

Selecting **6. Save & Exit** serializes your BST to `alice.json` and exits.

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
