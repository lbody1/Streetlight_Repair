# CS212 Data Structures - Course Project Report
# Project 77: Smart Streetlight Repair Desk (Environment & Smart Cities)

---

## 1. Cover Page Information
- **Course**: CS212 – Data Structures (Fall 2026–2027)
- **Institution**: Misr University for Science and Technology (MUST) - College of Information Technology
- **Project Title**: Smart Streetlight Repair Desk
- **Project Number / Idea**: 77 (Environment & Smart Cities)
- **Registered Practical Section**: [Insert Section Number, e.g., Section 3]
- **Team Members**:
  1. [Member 1 Name] - [University ID] (Team Leader / Architecture & Integration)
  2. [Member 2 Name] - [University ID] (Binary Search Tree & Search Logic)
  3. [Member 3 Name] - [University ID] (Linked List & Sorting Algorithm)
  4. [Member 4 Name] - [University ID] (Repair Queue FIFO Implementation)
  5. [Member 5 Name] - [University ID] (Repair Stack LIFO & Undo Implementation)
  6. [Member 6 Name] - [University ID] (Validation, Edge Cases & Documentation)

---

## 2. Problem Definition & Scope
### Problem Statement:
Municipalities manage thousands of streetlights spread across urban zones. Frequent lamp failures, cable faults, and weather damage lead to public safety risks and energy waste. Traditional manual paper reporting creates backlogs, untracked dispatches, lost citizen reports, and lack of accountability when repairs fail inspection.

### System Scope:
- **In Scope**:
  - Full municipal streetlight asset inventory tracking (Pole ID, location, lamp technology, status, brightness).
  - Fast hierarchical search and retrieval using unique Pole IDs.
  - Citizen / automated outage ticketing with FIFO technician dispatching.
  - LIFO repair action audit log supporting instant supervisor reversals (Undo).
  - On-demand sorting and multi-order tree traversal reporting.
- **Out of Scope**:
  - Direct hardware IoT sensor telemetry (simulated via status flags).
  - Real-time GPS geospatial mapping (simulated via street name strings).

---

## 3. Project Objectives
1. Provide a robust, menu-driven C++ system to register, decommission, update, and inspect streetlight assets.
2. Eliminate redundant reporting by validating existing assets and active tickets prior to queue insertion.
3. Implement fair FIFO (First-In, First-Out) technician assignment.
4. Guarantee auditability and quality control through LIFO (Last-In, First-Out) repair undo capabilities.
5. Strictly adhere to academic standards by manually building Linked Lists, BSTs, Queues, and Stacks without third-party or STL container libraries.

---

## 4. Data Structures Used & Technical Justification

| Data Structure | Role in Project 77 | Technical Justification |
| :--- | :--- | :--- |
| **Singly Linked List** (`LinkedList.h`) | Streetlight Asset Inventory | Provides dynamic memory growth with zero wasted pre-allocated space. Supports $O(1)$ front insertion and smooth node-to-node sequential traversals across varying municipality sizes. |
| **Binary Search Tree** (`BST.h`) | Unique Pole ID Index & Lookup | Solves the $O(n)$ search bottleneck of linear structures. Provides average $O(\log n)$ key lookup, insertion, and deletion. Inorder traversal yields naturally sorted ID reports without requiring external sorting. |
| **FIFO Queue** (`RepairQueue.h`) | Outage Tickets Awaiting Technicians | Guarantees fairness: oldest reported dark streets are serviced first ($O(1)$ enqueue and dequeue operations). Prevents outage neglect. |
| **LIFO Stack** (`RepairStack.h`) | Recent Completed Repairs & Undo Stack | The most recent repair is the first to be inspected during a quality audit. If a repair fails inspection, LIFO allows immediate $O(1)$ rollback and re-dispatch. |

---

## 5. System Features & Workflows

### Main Menu Options:
1. `Add New Streetlight`: Registers asset in Linked List and indexes in BST.
2. `Decommission Streetlight`: Synchronously removes node from Linked List and BST.
3. `Search Pole by ID`: Compares BST search ($O(\log n)$) against Linked List linear traversal ($O(n)$).
4. `Display Inventory`: Traverses Linked List to print formatted status table.
5. `Sort Inventory`: Performs Insertion Sort directly on Linked List nodes.
6. `BST Traversals`: Executes Inorder, Preorder, and Postorder traversals.
7. `Report Broken Light`: Verifies ID in BST, updates status to "Faulty", and enqueues ticket.
8. `View Repair Queue`: Displays pending tickets waiting for technicians.
9. `Dispatch Technician`: Dequeues front ticket, restores pole to "Operational", pushes to Stack.
10. `View Repair History`: Displays Stack contents from top to bottom.
11. `Undo Last Repair`: Pops top repair from Stack, reverts pole to "Faulty", re-enqueues ticket.
12. `System Summary`: Displays live node counts across all 4 structures.

---

## 6. Implementation Highlights (C++ Snippets & Explanations)

### A. BST Deletion (Handling 3 Cases - Lab 6 Slide 27):
```cpp
BSTNode* delNodeHelper(BSTNode* node, int x, bool& deleted) {
    if (node == nullptr) return nullptr;
    if (node->poleID > x) node->left = delNodeHelper(node->left, x, deleted);
    else if (node->poleID < x) node->right = delNodeHelper(node->right, x, deleted);
    else {
        deleted = true; nodeCount--;
        // Case 1 & 2: 0 or 1 child
        if (node->left == nullptr) { BSTNode* temp = node->right; delete node; return temp; }
        else if (node->right == nullptr) { BSTNode* temp = node->left; delete node; return temp; }
        // Case 3: 2 children -> replace with inorder successor
        BSTNode* succ = getSuccessor(node);
        node->poleID = succ->poleID;
        node->right = delNodeHelper(node->right, succ->poleID, deleted);
    }
    return node;
}
```

### B. Linked-List Queue Enqueue / Dequeue (Lab 5 Slide 25-26):
```cpp
void enqueue(const RepairTicket& ticket) {
    QueueNode* temp = new QueueNode(ticket);
    if (rearNode == nullptr) { frontNode = rearNode = temp; }
    else { rearNode->next = temp; rearNode = temp; }
    count++;
}
```

---

## 7. Comprehensive Testing Table

| Test Case | Category | Input Data | Expected Result | Actual Result | Status |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **TC-01** | Normal Insertion | Pole ID 115, "Cairo St", LED | Added to List & BST | Success message, count increments | PASS |
| **TC-02** | Duplicate Rejection | Pole ID 105 (already exists) | Error message; rejected | Duplicate rejected, BST prevents insert | PASS |
| **TC-03** | Empty Queue Dequeue | Option 9 when queue is 0 | Safe underflow warning | "No broken lights in queue" printed | PASS |
| **TC-04** | Empty Stack Undo | Option 11 when stack is 0 | Safe underflow warning | "Repair history stack is empty" printed | PASS |
| **TC-05** | Decommission Active | Delete Pole 102 | Removed from List & BST | Removed cleanly without memory leak | PASS |
| **TC-06** | End-to-End Undo | Report #101 -> Fix -> Undo | #101 returned to Faulty & Queue | Restored to Faulty, re-enqueued | PASS |
| **TC-07** | Invalid Menu Input | "abc" or 99 in menu | Reprompt safely | "Invalid input", menu loops | PASS |

---

## 8. Big-O Complexity Analysis

| Operation | Data Structure | Average Time | Worst Case | Space Complexity |
| :--- | :--- | :--- | :--- | :--- |
| **Search by Pole ID** | BST Index | $O(\log n)$ | $O(n)$ (skewed tree) | $O(1)$ |
| **Linear Search** | Singly Linked List | $O(n)$ | $O(n)$ | $O(1)$ |
| **Insert Asset** | Singly Linked List | $O(1)$ (begin) / $O(n)$ (end) | $O(n)$ | $O(1)$ |
| **Insert Asset** | BST Index | $O(\log n)$ | $O(n)$ | $O(1)$ |
| **Delete Asset** | BST Index | $O(\log n)$ | $O(n)$ | $O(1)$ |
| **Enqueue Fault** | FIFO Queue | $O(1)$ | $O(1)$ | $O(1)$ |
| **Dequeue Ticket** | FIFO Queue | $O(1)$ | $O(1)$ | $O(1)$ |
| **Push Repair** | LIFO Stack | $O(1)$ | $O(1)$ | $O(1)$ |
| **Pop / Undo Repair**| LIFO Stack | $O(1)$ | $O(1)$ | $O(1)$ |
| **Sort Inventory** | Insertion Sort (List) | $O(n^2)$ | $O(n^2)$ | $O(1)$ |

---

## 9. Team Contributions & Responsibilities
All members registered in the same section.
- **Member 1**: Architectural design, main menu integration, data consistency between structures.
- **Member 2**: Manual BST implementation (recursive insert, search, 3-case deletion, traversals).
- **Member 3**: Manual Singly Linked List implementation and Insertion Sort algorithm.
- **Member 4**: Manual FIFO Queue implementation (node structure, front/rear pointer tracking).
- **Member 5**: Manual LIFO Stack implementation and Undo reversal logic.
- **Member 6**: Input validation, test suite execution, screenshots, and report compilation.

---

## 10. Conclusion & Limitations
### Achieved Outcomes:
A completely standalone, zero-dependency C++ solution successfully integrating 4 manual data structures and an insertion sort algorithm with strict input validation and zero STL containers.

### Realistic Limitations:
1. **Unbalanced BST**: Successive sorted ID insertions may degenerate the BST into a linked list ($O(n)$ worst-case). An AVL tree with self-balancing rotations would solve this.
2. **Volatile Memory**: Data resides in RAM; integrating file I/O persistence (saving/loading from CSV/JSON) is a logical future enhancement.
