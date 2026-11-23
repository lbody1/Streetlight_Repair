#ifndef REPAIRQUEUE_H
#define REPAIRQUEUE_H

#include <iostream>
#include <string>

// Repair Request Ticket
struct RepairTicket {
    int poleID;
    std::string faultDescription;
    std::string reporterContact;
    std::string priority; // High, Medium, Low

    RepairTicket() : poleID(0), faultDescription(""), reporterContact(""), priority("Normal") {}

    RepairTicket(int id, std::string desc, std::string contact, std::string prio)
        : poleID(id), faultDescription(desc), reporterContact(contact), priority(prio) {}
};

// Queue Node (Linked-list representation matching Lab 5)
struct QueueNode {
    RepairTicket data;
    QueueNode* next;

    QueueNode(const RepairTicket& ticket) : data(ticket), next(nullptr) {}
};

// FIFO Queue for Broken Lights Awaiting Technicians (R3)
class RepairQueue {
private:
    QueueNode* frontNode;
    QueueNode* rearNode;
    int count;

public:
    RepairQueue() : frontNode(nullptr), rearNode(nullptr), count(0) {}

    ~RepairQueue() {
        clear();
    }

    bool isEmpty() const {
        return frontNode == nullptr;
    }

    int size() const {
        return count;
    }

    // Enqueue: add repair ticket to the rear (O(1))
    void enqueue(const RepairTicket& ticket) {
        QueueNode* temp = new QueueNode(ticket);
        if (rearNode == nullptr) {
            frontNode = rearNode = temp;
        } else {
            rearNode->next = temp;
            rearNode = temp;
        }
        count++;
    }

    // Dequeue: dispatch the front repair ticket to technician (O(1))
    bool dequeue(RepairTicket& outTicket) {
        if (isEmpty()) {
            return false;
        }
        QueueNode* temp = frontNode;
        outTicket = temp->data;
        frontNode = frontNode->next;

        if (frontNode == nullptr) {
            rearNode = nullptr; // Queue is now empty
        }

        delete temp;
        count--;
        return true;
    }

    // Peek: examine the next ticket awaiting technician without removal
    bool peek(RepairTicket& outTicket) const {
        if (isEmpty()) {
            return false;
        }
        outTicket = frontNode->data;
        return true;
    }

    // Display all waiting tickets
    void display() const {
        if (isEmpty()) {
            std::cout << " [No repair requests waiting in queue]\n";
            return;
        }
        std::cout << "\n--- Broken Lights Awaiting Technicians (FIFO Queue: " << count << " tickets) ---\n";
        QueueNode* temp = frontNode;
        int pos = 1;
        while (temp != nullptr) {
            std::cout << " #" << pos++ << " -> Pole ID: " << temp->data.poleID
                      << " | Priority: " << temp->data.priority
                      << " | Issue: " << temp->data.faultDescription
                      << " | Reporter: " << temp->data.reporterContact << "\n";
            temp = temp->next;
        }
        std::cout << "--------------------------------------------------------------------------\n";
    }

    // Check if a specific pole is already waiting in queue
    bool containsPole(int poleID) const {
        QueueNode* temp = frontNode;
        while (temp != nullptr) {
            if (temp->data.poleID == poleID) return true;
            temp = temp->next;
        }
        return false;
    }

    void clear() {
        RepairTicket dummy;
        while (dequeue(dummy)) {}
    }
};

#endif // REPAIRQUEUE_H
