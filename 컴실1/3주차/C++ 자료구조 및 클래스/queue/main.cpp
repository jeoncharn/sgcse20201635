#include <iostream>
#include <string>
#include "queue.h"
using namespace std;
int main(void)
{
    Queue q;
    int element;
    int menu;
    int popitem;
    bool success;
    while(1)
    {
        cout << endl;
        cout << "-----Menu-----" << endl;
        cout <<" 1. Enqueue " << endl;
        cout << " 2. Dequeue " << endl;
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
            q.enqueue(element);
        }
        else if(menu == 2)
        {
            success = q.dequeue(popitem);
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
            q.print();
            cout << endl;
        }
        else if(menu == 4)
        {
            cout << "Insert item to search" << endl;
            cin >> element;
            q.findItem(element);
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
