#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Streetlight.h"
#include <iostream>

// Singly Linked List Node
struct ListNode {
    Streetlight data;
    ListNode* next;

    ListNode(const Streetlight& light) : data(light), next(nullptr) {}
};

// Streetlight Inventory implemented as a Singly Linked List (R4)
class StreetlightInventory {
private:
    ListNode* head;
    int count;

public:
    StreetlightInventory() : head(nullptr), count(0) {}

    ~StreetlightInventory() {
        clear();
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    int size() const {
        return count;
    }

    // Insert at beginning (O(1))
    void insertBeginning(const Streetlight& light) {
        ListNode* newNode = new ListNode(light);
        newNode->next = head;
        head = newNode;
        count++;
    }

    // Insert at end (O(n))
    void insertEnd(const Streetlight& light) {
        ListNode* newNode = new ListNode(light);
        if (head == nullptr) {
            head = newNode;
        } else {
            ListNode* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        count++;
    }

    // Search by Pole ID (O(n) Linear Search)
    Streetlight* search(int id) {
        ListNode* temp = head;
        while (temp != nullptr) {
            if (temp->data.poleID == id) {
                return &(temp->data); // Return pointer to record for updates
            }
            temp = temp->next;
        }
        return nullptr;
    }

    // Delete node by Pole ID (O(n))
    bool deleteNode(int id) {
        if (head == nullptr) return false;

        ListNode* temp = head;
        ListNode* prev = nullptr;

        // If head node itself holds the key
        if (temp != nullptr && temp->data.poleID == id) {
            head = temp->next;
            delete temp;
            count--;
            return true;
        }

        // Search for the key to be deleted
        while (temp != nullptr && temp->data.poleID != id) {
            prev = temp;
            temp = temp->next;
        }

        // Key not found
        if (temp == nullptr) return false;

        // Unlink node from linked list
        prev->next = temp->next;
        delete temp;
        count--;
        return true;
    }

    // Traversal and display of all inventory records
    void display() const {
        if (head == nullptr) {
            std::cout << " [Inventory is empty]\n";
            return;
        }
        std::cout << "\n--- Current Streetlight Inventory (" << count << " poles) ---\n";
        ListNode* temp = head;
        while (temp != nullptr) {
            temp->data.display();
            temp = temp->next;
        }
        std::cout << "--------------------------------------------------------\n";
    }

    // Sorting algorithm (R6): Insertion Sort on Linked List
    // Sorts poles ascending by poleID
    void sortByID() {
        if (head == nullptr || head->next == nullptr) return;

        ListNode* sorted = nullptr;
        ListNode* current = head;

        while (current != nullptr) {
            ListNode* nextNode = current->next;

            // Insert current into sorted sublist
            if (sorted == nullptr || sorted->data.poleID >= current->data.poleID) {
                current->next = sorted;
                sorted = current;
            } else {
                ListNode* temp = sorted;
                while (temp->next != nullptr && temp->next->data.poleID < current->data.poleID) {
                    temp = temp->next;
                }
                current->next = temp->next;
                temp->next = current;
            }
            current = nextNode;
        }
        head = sorted;
        std::cout << " Inventory sorted by Pole ID using Insertion Sort.\n";
    }

    void clear() {
        ListNode* current = head;
        while (current != nullptr) {
            ListNode* nextNode = current->next;
            delete current;
            current = nextNode;
        }
        head = nullptr;
        count = 0;
    }
};

#endif // LINKEDLIST_H
