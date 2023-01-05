//typedef class Student Student;
#include "student.h"
Student::Student()
{
    cout << " Student class created " << endl;
}
Student::Student(const char input_grade)
{
    cout << " Student class created with grade " << endl;
    this->grade = input_grade;
}
Student::~Student()
{
    cout << " Student class destoryed " << endl;
}
void Student::update_grade(char grade)
{
    this->grade = grade;
}
/*
virtual void Student::update_name(string input_name)
{
    cout << " Name update in student class " << endl;
    this->name = input_name;
}
*/
// 다음과 같은 메소드는 부모 클래스의 private 데이터인 name을 사용한다.
// 그러므로 에러가 일어나게 됩니다.

void Student::update_money(int money)
{
    cout << " Money update in student class " << endl;
    this->money = money;
}
// 부모클래스에서 protected 로 선언된 데이터인 money를 자식 클래스에서는 접근 가능
char Student::show_grade()
{
    return this->grade;
}
