#include "person.h"
#include <iostream>
#include <string>
class Student : public Person{
    private:
        char grade;
    public:
        Student();
        Student(const char);
        ~Student();
        void update_grade(char grade);
//        void update_money(int);
        char show_grade();
        void update_money(int);
};

