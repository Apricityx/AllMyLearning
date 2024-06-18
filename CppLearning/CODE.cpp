#include <iostream>
#include <string>
using std::cout;
using std::string;

class Person {
public:
    Person(): name("Undefined"), age(0), sex("Male") {
    }

    string getSex() {
        return this->sex;
    }

protected:
    string name;
    int age;
    string sex;
};

int main() {
    Person *wzf = new Person;
    cout << wzf->getSex();
    delete wzf;
    return 0;
}
