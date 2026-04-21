#ifndef DWOKIERUNKOWA_H
#define DWOKIERUNKOWA_H

#include <iostream>

class Dwokierunkowa {
private:
    struct Node {
        int data;
        Node* next;
        Node* prev;

        Node(int d) : data(d), next(nullptr), prev(nullptr) {}
    };

    Node* head;
    Node* tail;
    int size;

public:
    Dwokierunkowa() {
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    Dwokierunkowa(const Dwokierunkowa& other) {
        head = nullptr;
        tail = nullptr;
        size = 0;

        Node* temp = other.head;
        while (temp != nullptr) {
            add_back(temp->data);
            temp = temp->next;
        }
    }

    ~Dwokierunkowa() {
        while (head != nullptr) {
            delete_front();
        }
    }

    int getsize() {
        return size;
    }

    void add_front(int x) {
        Node* newNode = new Node(x);

        if (head == nullptr) {
            head = tail = newNode;
        }
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }

        size++;
    }

    void add_back(int x) {
        Node* newNode = new Node(x);

        if (tail == nullptr) {
            head = tail = newNode;
        }
        else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }

        size++;
    }

    void add_index(int x, int index) {
        if (index < 0 or index > size) return;

        if (index == 0) {
            add_front(x);
            return;
        }

        if (index == size) {
            add_back(x);
            return;
        }

        Node* temp = head;
        for (int i = 0; i < index; i++) {
            temp = temp->next;
        }

        Node* newNode = new Node(x);

        newNode->next = temp;
        newNode->prev = temp->prev;

        temp->prev->next = newNode;
        temp->prev = newNode;

        size++;
    }

    void delete_front() {
        if (head == nullptr) return;

        Node* temp = head;
        head = head->next;

        if (head != nullptr)
            head->prev = nullptr;
        else
            tail = nullptr;

        delete temp;
        size--;
    }

    void delete_back() {
        if (tail == nullptr) return;

        Node* temp = tail;
        tail = tail->prev;

        if (tail != nullptr)
            tail->next = nullptr;
        else
            head = nullptr;

        delete temp;
        size--;
    }

    void delete_index(int index) {
        if (index < 0 || index >= size) return;

        if (index == 0) {
            delete_front();
            return;
        }

        if (index == size - 1) {
            delete_back();
            return;
        }

        Node* temp = head;
        for (int i = 0; i < index; i++) {
            temp = temp->next;
        }

        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;

        delete temp;
        size--;
    }

    int find(int x) {
        Node* temp = head;
        int index = 0;

        while (temp != nullptr) {
            if (temp->data == x) return index;
            temp = temp->next;
            index++;
        }

        return -1;
    }

    void print() {
        Node* temp = head;

        while (temp != nullptr) {
            std::cout << temp->data << " ";
            temp = temp->next;
        }

        std::cout << " ";
    }
};

#endif
