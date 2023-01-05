#include "stack.h"
Stack::Stack(){
    currentSize=0;
    MaxSize=MAX_SIZE;
    top = NULL;
}
Stack::Stack(int maxStackSize){
    currentSize = 0;
    MaxSize=maxStackSize;
    top = NULL;
}
Stack::~Stack(){
    Item i;
    while(isEmpty()){
        pop(i);
    }
}
bool Stack::push(const Item &item){
    if(isFull()) return false;
    Node *add = new Node;
    if(!add) return false;
    add->item = item;
    add->next = NULL;
    currentSize++;
    if(!top) top = add;
    else{
        add->next = top;
        top = add;
    }
    return true;
}
bool Stack::pop(Item &item){
    if(isEmpty()) return false;
    Node *tmp;
    currentSize--;
    item = top->item;
    tmp = top;
    top = top->next;
    tmp->next = NULL;
    delete(tmp);
    return true;
}
bool Stack::isEmpty(void) const{
    return currentSize==0;
}
bool Stack::isFull(void) const{
    return currentSize==MaxSize;
}
int Stack::stackCount(void) const{
    return currentSize;
}
void Stack::print(){
    int i;
    Node *tmp;
    if(isEmpty())
    {
        cout << "Stack is Empty" << endl;
    }
    tmp = top;
    for(i=0;i<currentSize;i++)
    {
        cout << i+1 << "th item is " << tmp->item << endl;
        tmp = tmp->next;
    }
}
void Stack::findItem(Item item)
{
    int i;
    Node *tmp;
    if(isEmpty())
    {
        cout << "Stack is Empty nothing to search" << endl;
    }
    tmp = top;
    for(i=0;i<currentSize;i++)
    {
        if(tmp->item == item)
        {
            cout << item << " is in " << i+1 << "th Node" << endl;
            return ;
        }
        tmp = tmp->next;
    }
    cout << "Search failed. item is not in the stack " << endl;
}
