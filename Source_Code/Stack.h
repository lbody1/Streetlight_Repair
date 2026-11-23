#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <string>

class RepairStack {
private:
    int poleIDs[100];
    std::string techNames[100];
    int topIndex;

public:
    RepairStack() {
        topIndex = -1;
    }

    bool isEmpty() const {
        return topIndex == -1;
    }

    bool isFull() const {
        return topIndex == 99;
    }

    int size() const {
        return topIndex + 1;
    }

    void push(int id, std::string tech) {
        if (isFull()) {
            std::cout << "Stack is full!\n";
            return;
        }
        topIndex++;
        poleIDs[topIndex] = id;
        techNames[topIndex] = tech;
    }

    int pop() {
        if (isEmpty()) {
            std::cout << "Stack is empty!\n";
            return -1;
        }
        int id = poleIDs[topIndex];
        topIndex--;
        return id;
    }

    int peek() const {
        if (isEmpty()) return -1;
        return poleIDs[topIndex];
    }

    void display() const {
        if (isEmpty()) {
            std::cout << "Stack is empty.\n";
            return;
        }
        std::cout << "--- Recent Repairs (LIFO) ---\n";
        for (int i = topIndex; i >= 0; i--) {
            std::cout << "Pole #" << poleIDs[i] << " | Tech: " << techNames[i] << "\n";
        }
    }
};

#endif
