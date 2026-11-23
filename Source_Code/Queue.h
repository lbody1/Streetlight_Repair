#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <string>

class RepairQueue {
private:
    int poleIDs[100];
    std::string issues[100];
    int frontIndex;
    int rearIndex;

public:
    RepairQueue() {
        frontIndex = -1;
        rearIndex = -1;
    }

    bool isEmpty() const {
        return (frontIndex == -1 || frontIndex > rearIndex);
    }

    bool isFull() const {
        return rearIndex == 99;
    }

    int size() const {
        if (isEmpty()) return 0;
        return (rearIndex - frontIndex + 1);
    }

    bool contains(int id) const {
        if (isEmpty()) return false;
        for (int i = frontIndex; i <= rearIndex; i++) {
            if (poleIDs[i] == id) return true;
        }
        return false;
    }

    void enqueue(int id, std::string issue) {
        if (isFull()) {
            std::cout << "Queue is full!\n";
            return;
        }
        if (frontIndex == -1) frontIndex = 0;
        rearIndex++;
        poleIDs[rearIndex] = id;
        issues[rearIndex] = issue;
    }

    int dequeue() {
        if (isEmpty()) {
            std::cout << "Queue is empty!\n";
            return -1;
        }
        int id = poleIDs[frontIndex];
        frontIndex++;
        if (frontIndex > rearIndex) {
            frontIndex = -1;
            rearIndex = -1;
        }
        return id;
    }

    int front() const {
        if (isEmpty()) return -1;
        return poleIDs[frontIndex];
    }

    void remove(int id) {
        if (isEmpty()) return;
        int k = frontIndex;
        for (int i = frontIndex; i <= rearIndex; i++) {
            if (poleIDs[i] != id) {
                poleIDs[k] = poleIDs[i];
                issues[k] = issues[i];
                k++;
            }
        }
        rearIndex = k - 1;
        if (frontIndex > rearIndex) {
            frontIndex = -1;
            rearIndex = -1;
        }
    }

    void display() const {
        if (isEmpty()) {
            std::cout << "Queue is empty.\n";
            return;
        }
        std::cout << "--- Waiting Lights (FIFO) ---\n";
        for (int i = frontIndex; i <= rearIndex; i++) {
            std::cout << "Pole #" << poleIDs[i] << " | Issue: " << issues[i] << "\n";
        }
    }
};

#endif
