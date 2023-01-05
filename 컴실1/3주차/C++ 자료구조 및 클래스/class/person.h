#include <iostream>
#include <string>
using namespace std;
class Person{
    private:
        int age;
        string name;
    protected:
        char bloodtype;
        int money;
    public:
        int id;
        Person();
        Person(const string );
        Person(int ,string );
        ~Person();
        void update_age(int age);
        void update_name(string name);
        void update_bloodtype(char bloodtype);
        int show_age();
        string show_name();
        char show_bloodtype();
        bool view_all();
};

