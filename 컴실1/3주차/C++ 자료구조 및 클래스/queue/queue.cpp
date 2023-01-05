#include "queue.h"
Queue::Queue(){
    currentSize=0;
    MaxSize=MAX_SIZE;
    top = NULL;
}
Queue::Queue(int maxStackSize){
    currentSize = 0;
    MaxSize=maxStackSize;
    top = NULL;
}
Queue::~Queue(){
    Item i;
    while(isEmpty()){
        dequeue(i);
    }
}
bool Queue::enqueue(const Item &item){
    if(isFull()) return false;
    Node *add = new Node;
    Node *tmp;
    if(!add) return false;
    add->item = item;
    add->next = NULL;
    currentSize++;
    if(!top) top = add;
    else{
        for(tmp=top;tmp->next!=NULL;tmp=tmp->next)
        {
//            cout << "tmp : " << tmp->item << endl;
        }
        tmp->next = add;
    }
    return true;
}
bool Queue::dequeue(Item &item){
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
bool Queue::isEmpty(void) const{
    return currentSize==0;
}
bool Queue::isFull(void) const{
    return currentSize==MaxSize;
}
int Queue::stackCount(void) const{
    return currentSize;
}
void Queue::print(){
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
void Queue::findItem(Item item)
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
