#pragma once

template <typename T>
struct Node {
    T value;
    Node<T>* next;

    Node() : next(nullptr) {}

    Node(T val_) : value(val_), next(nullptr) {}

    Node(T val_, Node<T>*next_ ) : value{val_}, next{next_} {}
};

template <typename T>
class LinkedList {
public:
    int size;
    Node<T>* head;

    LinkedList() : size(0), head(nullptr) {}

    ~LinkedList() {
        Node<T>* temp = head;
        while (temp != nullptr) {
            Node<T>* next = temp->next;
            delete temp;
            temp = next;
        }
    }

    void add_front(T val) {
        Node<T>* newNode = new Node<T>(val);
        newNode->next = head;
        head = newNode;
        size++;
    }

    void add_back(T val) {
        Node<T>* newNode = new Node<T>(val);

        if (head == nullptr) {
            head = newNode;
        } else {
            Node<T>* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        size++;
    }

    void add_at(T val, unsigned int index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
    }

    T& operator[](unsigned int index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }

        Node<T>* temp = head;
        int i = 0;

        while (temp != nullptr && i < index) {
            temp = temp->next;
            i++;
        }
        return temp->value;
    }
};