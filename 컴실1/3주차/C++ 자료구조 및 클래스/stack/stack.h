#include <iostream>
using namespace std;
#define MAX_SIZE 100
typedef int Item; // int를 스택의 자료 단위로 지정
struct Node{
    Item item; // 스택의 각 노드에 들어갈 데이터
    struct Node *next; // 다음 노드를 가리키는 포인터
};
class Stack{
    private: // 외부에서 직접 접근 불가
        Node *top; // 스택의 top을 지정하는 포인터
        int MaxSize; // 스택의 최대 크기
        int currentSize; // 스택의 현재 크기
    public: // 외부에서 직접 접근 가능
        Stack(); // 디폴트 생성자(스택의 크기가 최대 크기로 설정됨)
        Stack(int); // 스택의 최대 크기를 사용자가 정할 수 있는 생성자
        ~Stack(); // 소멸자
        bool isEmpty(void) const; // 스택이 비었는지를 판단하는 멤버 함수
        bool isFull(void) const; // 스택이 가득 찼는지를 판단
        int stackCount(void) const; // 스택에 노드가 몇 개 있는지를 판단
        bool push(const Item &item); // 스택에 새로운 노드를 삽입
        bool pop(Item &item); // 스택의 top에서 하나의 노드를 가져옴.
        void print();
        void findItem(Item item);
};
