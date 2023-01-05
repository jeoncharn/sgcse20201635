#include "person.h"
Person::Person()
{
    cout << "1. Person created" << endl;
}
// default 생성자
Person::Person(const string name)
{
    this->name = name;
    cout << "2. Person created with name" << endl;
}
Person::Person(int input_age,string input_name)
{
    this->age = input_age;
    this->name = input_name;
    cout << "3. Person created with age and name" << endl;
}
// overloading 을 이용해 여러개의 생성자 만듬
Person::~Person()
{
    cout << "Person destoryed" << endl;
}
void Person::update_age(int age)
{
    this->age = age;
}
// person class의 age를 업데이트
void Person::update_name(string name)
{
    this->name = name;
}
// person class의 name을 업데이트
void Person::update_bloodtype(char bloodtype)
{
    this->bloodtype = bloodtype;
}
// person 의 bloodtype을 업데이트
int Person::show_age()
{
    return this->age;
}
string Person::show_name()
{
    return this->name;
}
char Person::show_bloodtype()
{
    return this->bloodtype;
}
bool Person::view_all()
{
    cout << "Show all information of this person" << endl;
    cout << "Name is " << this->name << endl;
    cout << "Age is " << this->age << endl;
    cout << "Bloodtype is " << this->bloodtype << endl;
    cout << "Id is " << this->id << endl;
}
// 출력함수들

