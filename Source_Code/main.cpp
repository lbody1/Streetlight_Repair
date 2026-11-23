#include <iostream>
#include <string>
#include <limits>
#include <ctime>

#include "Streetlight.h"
#include "LinkedList.h"
#include "BST.h"
#include "RepairQueue.h"
#include "RepairStack.h"

using namespace std;

// Function to safely read an integer from console
int getValidInteger(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        } else {
            cout << " [Error] Invalid input. Please enter a valid number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

// Function to safely read a non-empty string
string getValidString(const string& prompt) {
    string str;
    while (true) {
        cout << prompt;
        getline(cin, str);
        if (!str.empty()) {
            return str;
        }
        cout << " [Error] Field cannot be empty.\n";
    }
}

// Current timestamp helper
string getCurrentTimeStr() {
    time_t now = time(0);
    char buf[80];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&now));
    return string(buf);
}

// Seed the system with initial realistic sample data
void seedInitialData(StreetlightInventory& inventory, PoleBSTIndex& bstIndex) {
    int initialIDs[] = {105, 102, 108, 101, 103, 107, 110};
    string streets[] = {
        "Main Boulevard",
        "Campus Avenue",
        "El-Tahrir Square",
        "University Ring Road",
        "North Industrial Way",
        "Green Valley Road",
        "South Gateway Street"
    };
    string types[] = {"LED 150W", "Sodium 250W", "Solar LED", "LED 100W", "LED 150W", "Solar LED", "LED 200W"};

    for (int i = 0; i < 7; i++) {
        Streetlight light(initialIDs[i], streets[i], types[i], "Operational", 100);
        inventory.insertEnd(light);
        bstIndex.insert(initialIDs[i]);
    }
}

int main() {
    StreetlightInventory inventory; // Linked List (R4)
    PoleBSTIndex bstIndex;          // Binary Search Tree (R5)
    RepairQueue repairQueue;        // Queue (R3)
    RepairStack repairStack;        // Stack (R2)

    // Pre-populate with realistic city data
    seedInitialData(inventory, bstIndex);

    int choice = 0;

    do {
        cout << "\n======================================================\n";
        cout << "      CS212 - SMART STREETLIGHT REPAIR DESK (P77)     \n";
        cout << "======================================================\n";
        cout << " [1] Add New Streetlight to Inventory (Linked List + BST)\n";
        cout << " [2] Decommission / Remove Streetlight (Linked List + BST)\n";
        cout << " [3] Search Pole by ID (BST O(log n) vs List O(n))\n";
        cout << " [4] Display All Streetlights in Inventory (Linked List)\n";
        cout << " [5] Sort Inventory by Pole ID (Insertion Sort - R6)\n";
        cout << " [6] Display BST Traversals (Inorder / Preorder / Postorder)\n";
        cout << "------------------------------------------------------\n";
        cout << " [7] Report Broken Streetlight (Enqueue to Repair Queue)\n";
        cout << " [8] View Broken Lights Awaiting Technicians (Queue Display)\n";
        cout << " [9] Dispatch Technician & Fix Light (Dequeue -> Push to Stack)\n";
        cout << " [10] View Recent Completed Repairs (Stack Display)\n";
        cout << " [11] Undo Last Completed Repair (Pop Stack -> Re-enqueue)\n";
        cout << "------------------------------------------------------\n";
        cout << " [12] System Summary & Structure Sizes\n";
        cout << " [13] Exit\n";
        cout << "======================================================\n";

        choice = getValidInteger(" Enter your choice [1-13]: ");

        switch (choice) {
            case 1: { // Add new pole
                cout << "\n--- Add New Streetlight Pole ---\n";
                int id = getValidInteger(" Enter Unique Pole ID: ");

                // Validation: Check duplicate ID in BST
                if (bstIndex.search(id)) {
                    cout << " [Error] Pole ID " << id << " already exists in system! Duplicate rejected.\n";
                    break;
                }

                string street = getValidString(" Enter Street / Location: ");
                string type = getValidString(" Enter Lamp Type (e.g. LED, Solar, Sodium): ");
                int brightness = getValidInteger(" Enter Brightness (0-100%): ");
                if (brightness < 0) brightness = 0;
                if (brightness > 100) brightness = 100;

                Streetlight newLight(id, street, type, "Operational", brightness);
                inventory.insertEnd(newLight);
                bstIndex.insert(id);

                cout << " [Success] Pole #" << id << " registered in Inventory and indexed in BST.\n";
                break;
            }

            case 2: { // Remove pole
                cout << "\n--- Decommission / Remove Streetlight ---\n";
                int id = getValidInteger(" Enter Pole ID to remove: ");

                // Check in BST
                if (!bstIndex.search(id)) {
                    cout << " [Error] Pole ID " << id << " does not exist in inventory.\n";
                    break;
                }

                // Check if pole is currently in repair queue
                if (repairQueue.containsPole(id)) {
                    cout << " [Warning] Pole #" << id << " has an active repair ticket in the queue.\n";
                }

                // Synchronized removal from both Linked List and BST
                bool listDeleted = inventory.deleteNode(id);
                bool bstDeleted = bstIndex.remove(id);

                if (listDeleted && bstDeleted) {
                    cout << " [Success] Pole #" << id << " successfully deleted from Inventory and BST Index.\n";
                } else {
                    cout << " [Warning] Synchronization mismatch during removal.\n";
                }
                break;
            }

            case 3: { // Search pole
                cout << "\n--- Search Streetlight by ID ---\n";
                int id = getValidInteger(" Enter Pole ID to search: ");

                cout << " Searching BST Index...";
                if (bstIndex.search(id)) {
                    cout << " Found in BST (O(log n) average time)!\n";
                    Streetlight* pole = inventory.search(id);
                    if (pole != nullptr) {
                        cout << " Details from Inventory:\n";
                        pole->display();
                    }
                } else {
                    cout << " NOT found in BST!\n";
                    cout << " Double-checking Linked List (Linear search O(n))... Not Found.\n";
                }
                break;
            }

            case 4: { // Display inventory
                inventory.display();
                break;
            }

            case 5: { // Sort inventory
                inventory.sortByID();
                inventory.display();
                break;
            }

            case 6: { // BST Traversals
                cout << "\n--- BST Index Traversals ---\n";
                cout << " Inorder Traversal (Sorted order):   ";
                bstIndex.inorder();
                cout << " Preorder Traversal (Root-Left-Right): ";
                bstIndex.preorder();
                cout << " Postorder Traversal (Left-Right-Root):";
                bstIndex.postorder();
                break;
            }

            case 7: { // Report broken light (Enqueue)
                cout << "\n--- Report Broken Streetlight ---\n";
                int id = getValidInteger(" Enter Faulty Pole ID: ");

                // Step 1: Validate existence via BST
                if (!bstIndex.search(id)) {
                    cout << " [Error] Pole ID " << id << " does not exist in municipality records!\n";
                    break;
                }

                // Step 2: Check if already queued
                if (repairQueue.containsPole(id)) {
                    cout << " [Notice] Pole #" << id << " is already in the repair queue awaiting technician.\n";
                    break;
                }

                // Step 3: Fetch record from inventory and update status
                Streetlight* pole = inventory.search(id);
                if (pole != nullptr) {
                    pole->status = "Faulty - Awaiting Repair";
                    pole->brightness = 0;
                }

                string faultDesc = getValidString(" Enter Fault Description (e.g. Burned Bulb, Broken Wire): ");
                string contact = getValidString(" Enter Reporter Contact / Department: ");
                string priority = getValidString(" Enter Priority (High / Medium / Low): ");

                RepairTicket ticket(id, faultDesc, contact, priority);
                repairQueue.enqueue(ticket);

                cout << " [Success] Repair ticket generated and enqueued (FIFO) for technician dispatch.\n";
                break;
            }

            case 8: { // View repair queue
                repairQueue.display();
                break;
            }

            case 9: { // Dispatch technician (Dequeue -> Push to Stack)
                cout << "\n--- Dispatch Technician & Repair Light ---\n";
                if (repairQueue.isEmpty()) {
                    cout << " [Info] No broken lights in queue. All systems operating normally.\n";
                    break;
                }

                RepairTicket nextTicket;
                repairQueue.dequeue(nextTicket);

                cout << " Dispatched ticket for Pole #" << nextTicket.poleID << " (" << nextTicket.faultDescription << ").\n";
                string techName = getValidString(" Enter Technician Name completing the repair: ");
                string details = getValidString(" Enter Action Taken (e.g. Replaced LED module, Fixed wiring): ");

                // Update inventory status back to Operational
                Streetlight* pole = inventory.search(nextTicket.poleID);
                if (pole != nullptr) {
                    pole->status = "Operational";
                    pole->brightness = 100;
                }

                // Push to Stack of completed repairs
                RepairLog log(nextTicket.poleID, techName, details, getCurrentTimeStr());
                repairStack.push(log);

                cout << " [Success] Pole #" << nextTicket.poleID 
                     << " restored to Operational status and repair logged to Stack (LIFO).\n";
                break;
            }

            case 10: { // View repair history (Stack)
                repairStack.display();
                break;
            }

            case 11: { // Undo last repair (Pop Stack -> Re-enqueue)
                cout << "\n--- Undo Last Completed Repair (LIFO Reversal) ---\n";
                if (repairStack.isEmpty()) {
                    cout << " [Info] Repair history stack is empty. Nothing to undo.\n";
                    break;
                }

                RepairLog lastLog;
                repairStack.pop(lastLog);

                cout << " Undoing repair on Pole #" << lastLog.poleID 
                     << " originally completed by " << lastLog.technicianName << ".\n";

                // Revert status in inventory
                Streetlight* pole = inventory.search(lastLog.poleID);
                if (pole != nullptr) {
                    pole->status = "Faulty - Repair Reverted";
                    pole->brightness = 0;
                }

                // Re-enqueue into repair queue with High Priority
                RepairTicket revertedTicket(lastLog.poleID, 
                                            "Audit Reversal: " + lastLog.resolutionDetails, 
                                            "Supervisor / Audit", 
                                            "High");
                repairQueue.enqueue(revertedTicket);

                cout << " [Success] Pole #" << lastLog.poleID 
                     << " reverted back to Faulty and re-enqueued into repair queue.\n";
                break;
            }

            case 12: { // System summary
                cout << "\n================ SYSTEM HEALTH & SUMMARY ================\n";
                cout << " Total Streetlight Poles in Inventory: " << inventory.size() << "\n";
                cout << " Total Poles Indexed in BST:          " << bstIndex.size() << "\n";
                cout << " Active Repair Requests in Queue:     " << repairQueue.size() << "\n";
                cout << " Completed Repairs Logged in Stack:   " << repairStack.size() << "\n";
                cout << "=========================================================\n";
                break;
            }

            case 13: { // Exit
                cout << "\n Exiting Streetlight Repair Desk. Saving session state. Goodbye!\n";
                break;
            }

            default:
                cout << " [Error] Invalid choice! Please select an option between 1 and 13.\n";
                break;
        }

    } while (choice != 13);

    return 0;
}
