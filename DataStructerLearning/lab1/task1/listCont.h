#ifndef LISTTEMP_H
#define LISTTEMP_H

template<class T>
class ListCont {
private:
    struct Node {
        T data;
        Node *next;
    };

    Node *head;
    int size;

public:

    ListCont(); //constructor

    ~ListCont(); //destructor

    int getSize() const; //get the number of elements

    bool isEmpty() const; //check whether the container is empty

    // Postcondition: A node with newData has been inserted at the
    //                head of the Linked container.
    void addHead(const T &newData); //Task 1: Please implement this!

};


//************************implementation of the linked list class template**************************
template<class T>
ListCont<T>::ListCont() {
    head = NULL; //empty list
    size = 0;
}

template<class T>
ListCont<T>::~ListCont() {
    Node *current = head;
    Node *temp;
    while (current != NULL) {
        temp = current;
        current = current->next;
        delete temp; //release
    }
}

template<class T>
int ListCont<T>::getSize() const {
    return size;
}

template<class T>
bool ListCont<T>::isEmpty() const {
    return size == 0;
}

template<class T>
void ListCont<T>::addHead(const T &newData) {
    //Task 1: Please implement this! todo
    Node *newNode = new Node;
    newNode->data = newData;
    newNode->next = head;
    head = newNode;
    size++;
}


#endif