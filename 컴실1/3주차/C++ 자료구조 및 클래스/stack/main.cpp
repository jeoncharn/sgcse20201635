#include <iostream>
#include <string>
#include "stack.h"
using namespace std;
int main(void)
{
    Stack s;
    int element;
    int menu;
    int popitem;
    bool success;
    while(1)
    {
        cout << endl;
        cout << "-----Menu-----" << endl;
        cout <<" 1. push " << endl;
        cout << " 2. pop " << endl;
        cout << " 3. print " << endl;
        cout << " 4. find " << endl;
        cout << " 5. quit " << endl;
        cout << "--------------" << endl;
        cout << endl;
        cin >> menu;
        if(menu == 1)
        {
            cout << "Insert element." << endl;
            cin >> element;
            s.push(element);
        }
        else if(menu == 2)
        {
            success = s.pop(popitem);
            if(success)
            {
                cout << "Element in the top of stack is " << popitem << endl;
            }
            else
            {
                cout << "Fail to pop" << endl;
            }
            cout << endl;
        }
        else if(menu ==3)
        {
            s.print();
            cout << endl;
        }
        else if(menu == 4)
        {
            cout << "Insert item to search" << endl;
            cin >> element;
            s.findItem(element);
            cout << endl;
        }
        else if(menu == 5)
        {
            cout << "bye" << endl;
            break;
        }
    }
    //s.print();
    //cout << "end" << endl;
    return 0;
}
