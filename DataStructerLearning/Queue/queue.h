//
// Created by apricityx on 24-11-6.
//

#ifndef QUEUE_H
#define QUEUE_H
#include <deque>

// 底层容器必须有以下操作：
// push_back
// pop_front
// front
// back
// size
// empty

template<class T, class Container = std::deque<T> >
class myQueue {
public:
    explicit myQueue(const Container &container = Container()) {
        this->c = container;
    }

    // explicit规定了只能通过显式调用构造函数来创建对象
    // 也就是说，只能通过myQueue<int> q;来创建对象，而不能通过myQueue<int> q = 1;来创建对象

    void push_back() {
        c.push_back();
    };

    void pop_front();

    T front();

    T back();

    size_t size();

    bool empty();

private:
    Container c;
};


#endif //QUEUE_H
