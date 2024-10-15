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
    void addHead(const T &newData);  //Task 1: please implement this!

    //************************declaration of the inner iterator class****************************
    //public inner class
    class Iterator {
        friend class ListCont<T>; //friend class of the iterator class
    private:
        Node *curr; //inner class can see the private type (i.e. Node) of the outer class?

        // Postcondition: The iterator has been constructed from ptr.
        Iterator(Node *ptr); //constructor with Node parameter, defined as private

    public:

        // Postcondition: The iterator has been constructed.
        Iterator(); //default constructor

        // Precondition: The iterator is positioned at an item.
        // Postcondition: The iterator has been positioned at
        // the next item in the Linked object.
        Iterator operator++(int); //post-increment of ++

        // Postcondition: A reference to the item the iterator
        // is positioned at has been returned.
        T &operator*() const;

        // Postcondition: true has been returned if the
        // iterator is equal to other; otherwise,
        // false has been returned.
        bool operator==(const Iterator other) const;

    };//class Iterator


    // Postcondition: An iterator positioned at the head of
    //                the Linked container has been returned.
    Iterator Begin() const;

    // Postcondition: An iterator positioned just AFTER the
    //                tail of the Linked container has been
    //                returned. NOT the position at the tail!
    Iterator End() const;

};


//************************implementation of the iterator inner class**************************
template<class T>
ListCont<T>::Iterator::Iterator() //default constructor
{
    curr = NULL;
}

template<class T>
ListCont<T>::Iterator::Iterator(Node *ptr) {
    curr = ptr;
}

template<class T>
typename ListCont<T>::Iterator ListCont<T>::Iterator::operator++(int) //typename for dependent type
{
    Iterator temp = *this; //default copy constructor
    this->curr = curr->next;
    return temp; //return iterator object
}

template<class T>
T &ListCont<T>::Iterator::operator*() const {
    return curr->data; //return data reference
}

template<class T>
bool ListCont<T>::Iterator::operator==(const Iterator other) const {
    return curr == other.curr;
}


//************************implementation of the Begin and End position**************************
template<class T>
typename ListCont<T>::Iterator ListCont<T>::Begin() const {
    return Iterator(head); //container class call the private method (constructor) of the Iterator class:
    //friend class is required
}

template<class T>
typename ListCont<T>::Iterator ListCont<T>::End() const {
    return Iterator(); //NULL pointer
}


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
    //Task 1: Please implement this!
    Node *newNode = new Node;
    newNode->data = newData;
    newNode->next = head;
    head = newNode;
    size++;
}


#endif