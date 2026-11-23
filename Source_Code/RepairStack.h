#ifndef REPAIRSTACK_H
#define REPAIRSTACK_H

#include <iostream>
#include <string>

// Record of a completed repair
struct RepairLog {
    int poleID;
    std::string technicianName;
    std::string resolutionDetails;
    std::string timestamp;

    RepairLog() : poleID(0), technicianName(""), resolutionDetails(""), timestamp("") {}

    RepairLog(int id, std::string tech, std::string details, std::string time)
        : poleID(id), technicianName(tech), resolutionDetails(details), timestamp(time) {}
};

// Stack Node (Linked-list representation matching Lab 5)
struct StackNode {
    RepairLog data;
    StackNode* next;

    StackNode(const RepairLog& log) : data(log), next(nullptr) {}
};

// LIFO Stack for Recent Repairs & Undo History (R2)
class RepairStack {
private:
    StackNode* topNode;
    int count;

public:
    RepairStack() : topNode(nullptr), count(0) {}

    ~RepairStack() {
        clear();
    }

    bool isEmpty() const {
        return topNode == nullptr;
    }

    int size() const {
        return count;
    }

    // Push: record a completed repair (O(1))
    void push(const RepairLog& log) {
        StackNode* newNode = new StackNode(log);
        newNode->next = topNode;
        topNode = newNode;
        count++;
    }

    // Pop: undo the last completed repair (O(1))
    bool pop(RepairLog& outLog) {
        if (isEmpty()) {
            return false;
        }
        StackNode* temp = topNode;
        outLog = temp->data;
        topNode = topNode->next;
        delete temp;
        count--;
        return true;
    }

    // Peek: view most recent repair without removing
    bool peek(RepairLog& outLog) const {
        if (isEmpty()) {
            return false;
        }
        outLog = topNode->data;
        return true;
    }

    // Display history of repairs (top to bottom)
    void display() const {
        if (isEmpty()) {
            std::cout << " [No repair history in stack]\n";
            return;
        }
        std::cout << "\n--- Recent Completed Repairs (LIFO Stack: " << count << " records) ---\n";
        StackNode* temp = topNode;
        int step = 1;
        while (temp != nullptr) {
            std::cout << " " << step++ << ") Pole ID: " << temp->data.poleID
                      << " | Technician: " << temp->data.technicianName
                      << " | Action: " << temp->data.resolutionDetails
                      << " | Date/Time: " << temp->data.timestamp << "\n";
            temp = temp->next;
        }
        std::cout << "--------------------------------------------------------------------\n";
    }

    void clear() {
        RepairLog dummy;
        while (pop(dummy)) {}
    }
};

#endif // REPAIRSTACK_H
