#include <iostream>
#include <string>

#include "Streetlight.h"
#include "LinkedList.h"
#include "BST.h"
#include "Queue.h"
#include "Stack.h"

using namespace std;

int readInt() {
    int x;
    while (!(cin >> x)) {
        if (cin.eof()) return 0;
        cout << "Invalid input. Enter a number: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }
    return x;
}

string readString() {
    string s;
    getline(cin >> ws, s);
    return s;
}

int main() {
    StreetlightList inventory;
    PoleBST bst;
    RepairQueue queue;
    RepairStack stack;

    // Initial sample data
    inventory.insert(105, "Main Boulevard", "Working");
    bst.insert(105);

    inventory.insert(102, "Campus Avenue", "Working");
    bst.insert(102);

    inventory.insert(108, "Tahrir Square", "Working");
    bst.insert(108);

    inventory.insert(101, "University Road", "Working");
    bst.insert(101);

    int choice, id;
    string street, issue, tech;

    do {
        cout << "\n============================================\n";
        cout << "      STREETLIGHT REPAIR DESK (CS212)       \n";
        cout << "============================================\n";
        cout << "1.  Add New Pole\n";
        cout << "2.  Delete Pole\n";
        cout << "3.  Update Street Name\n";
        cout << "4.  Display Inventory (Linked List)\n";
        cout << "5.  Search Pole (BST)\n";
        cout << "6.  BST Traversals (Inorder, Preorder, Postorder)\n";
        cout << "7.  Report Broken Light (Enqueue)\n";
        cout << "8.  Repair Next Light (Dequeue -> Push to Stack)\n";
        cout << "9.  View Queue and Stack\n";
        cout << "10. Undo Last Repair (Pop -> Re-enqueue)\n";
        cout << "11. Sort Inventory by Street (Bubble Sort)\n";
        cout << "12. Display System Status\n";
        cout << "0.  Exit\n";
        cout << "Enter your choice: ";
        choice = readInt();

        switch (choice) {
            case 1: {
                cout << "Enter Pole ID: ";
                id = readInt();
                if (id <= 0) {
                    cout << "ID must be greater than 0.\n";
                } else if (bst.search(id)) {
                    cout << "Pole ID already exists! Duplicate rejected.\n";
                } else {
                    cout << "Enter Street Name: ";
                    street = readString();
                    inventory.insert(id, street, "Working");
                    bst.insert(id);
                    cout << "Pole #" << id << " added successfully.\n";
                }
                break;
            }

            case 2: {
                cout << "Enter Pole ID to delete: ";
                id = readInt();
                if (!bst.search(id)) {
                    cout << "Pole ID not found!\n";
                } else {
                    inventory.remove(id);
                    bst.remove(id);
                    queue.remove(id);
                    cout << "Pole #" << id << " deleted.\n";
                }
                break;
            }

            case 3: {
                cout << "Enter Pole ID to update: ";
                id = readInt();
                Streetlight* pole = inventory.search(id);
                if (pole == NULL) {
                    cout << "Pole not found!\n";
                } else {
                    cout << "Enter New Street Name: ";
                    pole->street = readString();
                    cout << "Street updated successfully.\n";
                }
                break;
            }

            case 4: {
                inventory.display();
                break;
            }

            case 5: {
                cout << "Enter Pole ID to search: ";
                id = readInt();
                if (bst.search(id)) {
                    Streetlight* pole = inventory.search(id);
                    cout << "Found in BST -> Pole #" << pole->id 
                         << " | Street: " << pole->street 
                         << " | Status: " << pole->status << "\n";
                } else {
                    cout << "Pole not found in BST.\n";
                }
                break;
            }

            case 6: {
                cout << "Inorder:   "; bst.inorder();
                cout << "Preorder:  "; bst.preorder();
                cout << "Postorder: "; bst.postorder();
                break;
            }

            case 7: {
                cout << "Enter Broken Pole ID: ";
                id = readInt();
                Streetlight* pole = inventory.search(id);
                if (pole == NULL) {
                    cout << "Pole not found in records!\n";
                } else if (queue.contains(id)) {
                    cout << "Pole is already in the repair queue!\n";
                } else if (queue.isFull()) {
                    cout << "Queue is full!\n";
                } else {
                    cout << "Enter Fault Issue: ";
                    issue = readString();
                    pole->status = "Broken";
                    queue.enqueue(id, issue);
                    cout << "Pole #" << id << " added to repair queue.\n";
                }
                break;
            }

            case 8: {
                if (queue.isEmpty()) {
                    cout << "No broken lights in queue.\n";
                } else {
                    int nextPole = queue.front();
                    cout << "Repairing Pole #" << nextPole << "\n";
                    cout << "Enter Technician Name: ";
                    tech = readString();
                    id = queue.dequeue();
                    Streetlight* pole = inventory.search(id);
                    if (pole != NULL) {
                        pole->status = "Working";
                    }
                    stack.push(id, tech);
                    cout << "Pole #" << id << " repaired and saved to stack.\n";
                }
                break;
            }

            case 9: {
                queue.display();
                cout << "\n";
                stack.display();
                break;
            }

            case 10: {
                if (stack.isEmpty()) {
                    cout << "No recent repairs to undo.\n";
                } else {
                    id = stack.pop();
                    Streetlight* pole = inventory.search(id);
                    if (pole != NULL) {
                        pole->status = "Broken";
                        queue.enqueue(id, "Reopened Repair");
                        cout << "Undo complete: Pole #" << id << " marked broken and returned to queue.\n";
                    }
                }
                break;
            }

            case 11: {
                inventory.sortByStreet();
                break;
            }

            case 12: {
                cout << "--- System Status ---\n";
                cout << "Total Poles in Inventory : " << inventory.count() << "\n";
                cout << "Waiting in Queue         : " << queue.size() << "/100\n";
                cout << "Repairs in Stack         : " << stack.size() << "/100\n";
                break;
            }

            case 0: {
                cout << "Exiting. Goodbye!\n";
                break;
            }

            default:
                cout << "Invalid choice! Try again.\n";
        }

    } while (choice != 0);

    return 0;
}
