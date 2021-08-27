#include "STACK.h"
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

template <typename T> //析构函数
bool STACK<T>::DestroyStack()
{
    if (length == 0)
        return true;
    Item *temp;
    while (top != nullptr)
    {
        temp = top;
        top = top->next;
        delete temp;
    }
    length = 0;
    return true;
}

template <typename T> //保留，此处是链表的物理结构，留待数组物理结构的接口使用
bool STACK<T>::ClearStack()
{
    this->DestroyStack();
    return true;
}

template <typename T> //返回STACK的占用长度
bool STACK<T>::StackEmpty()
{
    return length == 0;
}

template <typename T> //压入操作
bool STACK<T>::push(T data)
{
    length++;
    Item *temp = new Item;
    temp->data = data;
    if (top == nullptr)
    {
        top = temp;
        temp->next = nullptr;
        return true;
    }
    temp->next = top;
    top = temp;
    return true;
}

template <typename T> //弹出操作
T STACK<T>::pop()
{
    if (length == 0)
        return false;
    T temp;
    Item *p;
    temp = top->data;
    p = top;
    top = top->next;
    delete p;
    length--;
    return temp;
}

int main()
{
    STACK<int> a;
    cout << a.getTop();
    cout << a.pop();
    a.push(1);
    a.push(2);
    cout << a.pop();
    system("pause");
}