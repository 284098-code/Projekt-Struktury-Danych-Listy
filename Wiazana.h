#ifndef WIAZANA
#define WIAZANA

#include <iostream>

class Wiazana {
private:
    struct Node {
        int data;
        Node* next;

        Node(int d) : data(d), next(nullptr) {}
    };

    Node* head;
    int size;

public:
    Wiazana() {
        head = nullptr;
        size = 0;
    }

    Wiazana(const Wiazana& other) {
        head = nullptr;
        size = 0;

        Node* temp = other.head;
        while (temp != nullptr) {
            add_back(temp->data);
            temp = temp->next;
        }
    }

    ~Wiazana() {
        while (head != nullptr) {
            delete_front();
        }
    }

    int getsize() {
        return size;
    }


    void add_back(int i) {
        Node* newNode = new Node(i);

        if (head == nullptr) {
            head = newNode;
        }
        else {
            Node* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }

        size++;
    }

    void add_front(int i) {
        Node* newNode = new Node(i);
        newNode->next = head;
        head = newNode;
        size++;
    }

    void add_index(int i, int index) {
        if (index < 0 or index > size) return;

        if (index == 0) {
            add_front(i);
            return;
        }

        Node* newNode = new Node(i);
        Node* temp = head;

        for (int i = 0; i < index - 1; i++) {
            temp = temp->next;
        }

        newNode->next = temp->next;
        temp->next = newNode;
        size++;
    }

    void delete_front() {
        if (head == nullptr) return;

        Node* temp = head;
        head = head->next;
        delete temp;
        size--;
    }

    void delete_back() {
        if (head == nullptr) return;

        if (head->next == nullptr) {
            delete head;
            head = nullptr;
            size--;
            return;
        }

        Node* temp = head;
        while (temp->next->next != nullptr) {
            temp = temp->next;
        }

        delete temp->next;
        temp->next = nullptr;
        size--;
    }

    void delete_index(int index) {
        if (index < 0 or index >= size) return;

        if (index == 0) {
            delete_front();
            return;
        }

        Node* temp = head;

        for (int i = 0; i < index - 1; i++) {
            temp = temp->next;
        }

        Node* toDelete = temp->next;
        temp->next = temp->next->next;
        delete toDelete;

        size--;
    }


    int find(int i) {
        Node* temp = head;
        int index = 0;

        while (temp != nullptr) {
            if (temp->data == i) {
                return index;
            }
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
