# CS212 - Data Structures Course Project
## Project 77: Streetlight Repair Desk (Environment & Smart Cities)

### 📌 Overview
Streetlight Repair Desk is an integrated, console-driven C++ application designed to manage municipal streetlight infrastructure, log resident outage reports, dispatch repair crews, and maintain a LIFO undo/audit history of maintenance actions.

The application strictly implements manual, non-STL data structures in accordance with CS212 specifications:
1. **Linked List (`LinkedList.h`)**: Singly linked list storing the complete municipal streetlight inventory. Supports insertion, deletion, linear search, traversal, and Insertion Sort.
2. **Binary Search Tree (`BST.h`)**: Hierarchical tree indexing streetlights by unique `poleID` for $O(\log n)$ lookup and deletion (handles 0, 1, and 2 children via inorder successor), plus Inorder, Preorder, and Postorder traversals.
3. **Queue (`RepairQueue.h`)**: FIFO linked-list queue managing reported faulty streetlights awaiting technician dispatch.
4. **Stack (`RepairStack.h`)**: LIFO linked-list stack preserving a history of completed repairs and enabling supervisor undo reversals.

---

### 📂 Repository Structure
```text
CS212_Streetlight_Repair/
├── README.md                          # Build, run, and architecture documentation
├── Source_Code/                       # Complete C++ source files
│   ├── Streetlight.h                  # Data model for streetlight records
│   ├── LinkedList.h                   # Manual singly linked list implementation
│   ├── BST.h                          # Manual Binary Search Tree implementation
│   ├── RepairQueue.h                  # Manual FIFO Queue implementation
│   ├── RepairStack.h                  # Manual LIFO Stack implementation
│   └── main.cpp                       # Interactive console application and workflow
├── Tests/                             # Test cases and automated input script
│   └── test_inputs.txt                # Sample batch inputs for demonstration
└── Report/                            # Formal project report (PDF / DOCX)
```

---

### ⚙️ Compilation and Execution Instructions

#### Prerequisites:
- A C++11 compliant compiler (e.g. GCC/G++ or Clang or MSVC).
- Windows PowerShell or Command Prompt / Linux Terminal.

#### How to Compile:
Navigate to the `Source_Code` directory:
```powershell
cd Source_Code
g++ -std=c++11 -Wall -Wextra main.cpp -o streetlight_app.exe
```

#### How to Run:
```powershell
.\streetlight_app.exe
```

#### Running Automated Test Script:
To execute the automated end-to-end test suite:
```powershell
Get-Content ..\Tests\test_inputs.txt | .\streetlight_app.exe
```

---

### 🔄 End-to-End Workflow & Integration
1. **Inventory Registration**: Adding a new pole registers it into the `StreetlightInventory` (Linked List) and inserts its ID into `PoleBSTIndex` (BST). Duplicate IDs are rejected with validation messages.
2. **Outage Reporting (FIFO)**: When an outage is reported, the pole is verified via BST ($O(\log n)$), its status is updated to "Faulty", and a ticket is enqueued into `RepairQueue`.
3. **Technician Dispatch**: Dequeuing the next ticket dispatches the technician, updates the streetlight back to "Operational" (100% brightness), and logs the completion into `RepairStack` (LIFO).
4. **Supervisor Undo / Audit (LIFO)**: Popping from `RepairStack` reverses the latest repair, flags the pole as "Faulty - Repair Reverted", and re-enqueues it with high priority.
5. **Decommissioning**: Removing a pole safely purges it from both the Linked List and the BST, ensuring zero dangling pointers or index mismatches.
