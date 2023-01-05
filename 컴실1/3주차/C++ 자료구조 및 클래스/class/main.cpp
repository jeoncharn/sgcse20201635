// 실습에 도움이 될 수 있는 기초적인 코드입니다. 헤더파일과 cpp 파일을 참조해서
// 함수를 바꿔가면서 실행해보세요.
// 오류 발견시 조교에게 알려주시면 수정 및 feedback을 해드리겠습니다.
#include "student.h"
#include <string>
int main(void)
{
    string name = "soon";
    /*
       Person p;
       p(25,name);
       // 다음과 같이 실행하면 생성자에서 오류가 발생합니다.
       // 꼭 아래 라인의 Person p(25,name)과 같이 생성해야 합니다. 
       // 생성자를 보고 생성하셔야 됩니다. 생성자를 여러개 선언해놓았을때  Person p; 해놓고 p(name) 과 같이 사용하시면 에러가 납니다.
    */
    Person e(name);
    Person t;
    Person p(25,name);
    cout << "age : " <<  p.show_age() << "name : " << p.show_name() << endl;
    Student s('a');
    // 생성자에서 출력되는 부분을 보면 부모 클래스인 Person이 생성되고
    // 자식 클래스인 Student가 생성되는 것을 알 수있다.
    // 프로그램이 끝날때는 반대로 Student가 먼저 해제되고 Person이 그 다음 순서이다.
    name = "Student1";
    s.update_name(name);
    s.update_age(20);
    // 자식 클래스에서는 정의 되어있지 않지만 부모 클래스에서 정의되어있기 때문에 사용이 가능합니다.
    // code의 재사용성을 보여주는 부분입니다.
    s.id = 15;
    // public으로 선언된 데이터 이기 때문에 main에서 바로 접근할 수 있습니다.
    s.update_bloodtype('o');
    s.update_money(10000);
    //s.money = 10;
    //s.age = 12 ; 이런석으로 하시면 age가 Person class에서 private 이므로 오류가 납니다. 
    //하지만 money은 protected 이기 때문에 하위 클래스인 Student에서 바로 접근 가능합니다.
    // 그렇지만 여기는 Student class가 아닌 main함수이기때문에 s.money = 15 와 같이 사용하는 것은 불가능합니다.
    s.view_all();
    return 0;
}
