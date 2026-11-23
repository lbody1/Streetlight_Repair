#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Streetlight.h"
#include <iostream>

struct ListNode {
    Streetlight data;
    ListNode* next;

    ListNode(Streetlight light) : data(light), next(NULL) {}
};

class StreetlightList {
private:
    ListNode* head;

public:
    StreetlightList() : head(NULL) {}

    ~StreetlightList() {
        ListNode* curr = head;
        while (curr != NULL) {
            ListNode* nxt = curr->next;
            delete curr;
            curr = nxt;
        }
        head = NULL;
    }

    bool isEmpty() const {
        return head == NULL;
    }

    void insert(int id, std::string street, std::string status) {
        Streetlight light(id, street, status);
        ListNode* newNode = new ListNode(light);

        if (head == NULL) {
            head = newNode;
            return;
        }
        ListNode* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    Streetlight* search(int id) {
        ListNode* temp = head;
        while (temp != NULL) {
            if (temp->data.id == id) {
                return &(temp->data);
            }
            temp = temp->next;
        }
        return NULL;
    }

    void remove(int id) {
        if (head == NULL) return;

        ListNode* temp = head;
        ListNode* prev = NULL;

        if (temp != NULL && temp->data.id == id) {
            head = temp->next;
            delete temp;
            return;
        }

        while (temp != NULL && temp->data.id != id) {
            prev = temp;
            temp = temp->next;
        }

        if (temp == NULL) return;

        prev->next = temp->next;
        delete temp;
    }

    int count() const {
        int c = 0;
        ListNode* temp = head;
        while (temp != NULL) {
            c++;
            temp = temp->next;
        }
        return c;
    }

    void display() const {
        if (head == NULL) {
            std::cout << "Inventory is empty.\n";
            return;
        }
        std::cout << "--- Streetlight Inventory (" << count() << " poles) ---\n";
        ListNode* temp = head;
        while (temp != NULL) {
            std::cout << "ID: " << temp->data.id 
                      << " | Street: " << temp->data.street 
                      << " | Status: " << temp->data.status << "\n";
            temp = temp->next;
        }
    }

    void sortByStreet() {
        if (head == NULL || head->next == NULL) return;

        for (ListNode* i = head; i != NULL; i = i->next) {
            for (ListNode* j = i->next; j != NULL; j = j->next) {
                if (i->data.street > j->data.street) {
                    Streetlight temp = i->data;
                    i->data = j->data;
                    j->data = temp;
                }
            }
        }
        std::cout << "Inventory sorted by street name.\n";
        display();
    }
};

#endif
