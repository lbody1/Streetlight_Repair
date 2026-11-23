# CS212 Data Structures Course Project
## Project 77: Streetlight Repair Desk

### Project Description
A menu-driven C++ application to manage municipal streetlights, handle repair requests, and maintain repair history. The system uses manually implemented data structures according to the course curriculum:
- **Stack**: Array-based stack (LIFO) to store recent completed repairs and handle undo operations.
- **Queue**: Array-based queue (FIFO) to manage broken streetlights waiting for technicians.
- **Linked List**: Singly linked list storing the streetlight inventory with Bubble Sort to sort by street name.
- **Binary Search Tree (BST)**: Binary search tree for fast pole ID search, insertion, deletion, and tree traversals.

---

### Team Members (Section: CRN 7182 - Team 77)
| # | Name | Student ID |
|---|------|------------|
| 1 | Mohamed Ahmed Abdelkhalek Gohary | 200038102 |
| 2 | Yusuf Ahmed Muhammad Sayed | 200067726 |
| 3 | Bilal Mahmoud Fahmy Mahmoud | 200069114 |
| 4 | Abdelrahman Salah Ibrahim Abdelwahab | 200070046 |
| 5 | Abdul-Azim Ibrahim Abdul-Azim Ibrahim Jabr | 200073612 |
| 6 | Hamza Abdelfattah Elazab Fayad | 200083256 |

---

### Folder Structure
```text
Streetlight_Repair/
├── Source_Code/
│   ├── Streetlight.h
│   ├── LinkedList.h
│   ├── BST.h
│   ├── Queue.h
│   ├── Stack.h
│   └── main.cpp
├── Report/
│   └── CS212_Project_77_Streetlight_Repair_Desk_Report.docx
├── Screenshots/
├── Tests/
│   ├── test_cases_documentation.md
│   └── test_inputs.txt
├── build.bat
└── README.md
```

---

### How to Compile and Run

#### Windows (Using build.bat):
Double click on `build.bat` in the root folder.

#### Command Line (g++):
```powershell
cd Source_Code
g++ -std=c++11 main.cpp -o app.exe
.\app.exe
```
