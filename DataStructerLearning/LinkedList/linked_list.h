#ifndef LINKED
#define LINKED

template<class T>
class Linked {

protected:
    struct Node {
        ///----(1)-----/// todo
        Node *next;
        T item;
    }; // struct Node

    Node *head;
    long length;

public:
    class Iterator {

        ///----(2)-----/// todo
        friend class Linked;

    protected:
        Node *nodePtr;

        // Postcondition: The iterator has been constructed
        //                from newPtr.
        Iterator(Node *newPtr) {
            nodePtr = newPtr;
        } // constructor


    public:

        // Postcondition: The iterator has been constructed.
        Iterator() {
        } // default constructor


        // Postcondition: true has been returned if the
        //                iterator is equal to itr; otherwise,
        //                false has been returned.
        bool operator==(const Iterator &itr) const {
            return nodePtr == itr.nodePtr;
        } // overloading ==


        // Postcondition: true has been returned if the
        //                iterator is not equal to itr;
        //                otherwise, false has been returned.
        bool operator!=(const Iterator &itr) const {
            return nodePtr != itr.nodePtr;
        } // overloading !=


        // Postcondition: A reference to the item the iterator
        //                is positioned at has been returned.
        T &operator*() const {
            return nodePtr->item;
        } // overloading *


        // Precondition: The iterator is positioned at an item.
        // Postcondition: The iterator has been positioned at
        //                the next item in the Linked object.
        Iterator operator++(int) {
            Iterator temp = *this;
            nodePtr = nodePtr->next;
            return temp;
        } // post-increment ++


        // Precondition: The iterator is positioned at an item.
        // Postcondition: The iterator has been positioned at
        //                the next item in the Linked object.
        Iterator &operator++() {
            ///----(3)-----/// todo
            nodePtr = nodePtr->next;
            return *this;
        } // pre-increment ++

    }; // class Iterator


    // Postcondition: The Linked container has been initialized
    //                to an empty container.
    Linked() {
        head = NULL;
        length = 0;
    } // default constructor


    // Postcondition: The number of items in the Linked container
    //                has been returned.
    long size() {
        return length;
    } // size


    // Postcondition: A node with newItem has been inserted at the
    //                front of the Linked container.
    void push_front(const T &newItem) {
        Node *newHead = new Node;
        newHead->item = newItem;
        newHead->next = head;
        head = newHead;
        length++;
    } // push_front


    // Precondition: The Linked container is not empty.
    // Postcondition: The front item has been deleted from the
    //                Linked container.
    void pop_front() {
        Node *oldHead = head;
        head = head->next;
        delete oldHead;
        length--;
    } // method popFront


    // Postcondition: a copy of otherLinked has been stored in
    //                this Linked container and returned.
    Linked<T> &operator=(const Linked<T> &otherLinked) {
        Linked<T> tempLinked;

        Node *tempPtr;

        // Destroy the calling object:
        while (head != NULL)
            pop_front();

        // Copy otherLinked to tempLinked, in reverse order.
        for (tempPtr = otherLinked.head; tempPtr != NULL;
             tempPtr = tempPtr->next)
            tempLinked.push_front(tempPtr->item);

        // Copy tempLinked to Linked container, in reverse order.
        // So Linked container has copy of otherLinked in order.
        for (tempPtr = tempLinked.head; tempPtr != NULL;
             tempPtr = tempPtr->next)
            push_front(tempPtr->item);
        return *this;
    } // overloading =


    // Postcondition: An iterator positioned at the front of
    //                the Linked container has been returned.
    Iterator begin() {
        ///----(4)-----/// todo
        return Iterator(head);
    } // begin


    // Postcondition: An iterator positioned just after the
    //                back of the Linked container has been
    //                returned.
    Iterator end() {
        return Iterator(NULL);
    } // end


    // Postcondition: The space allocated for the Linked object has
    //                been deallocated.
    ~Linked() {
        ////------(5)-------//// todo
        while (head != nullptr) {
            pop_front();
        }
    } // destructor
}; // class Linked

#endif
