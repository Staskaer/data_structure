#include "QUEUE.h"
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

template <typename T> //析构函数
bool QUEUE<T>::DestroyQueue()
{
    if (length == 0)
        return true;
    Item *temp;
    while (front != rear)
    {
        temp = front;
        front = front->next;
        delete temp;
    }
    return true;
}

template <typename T> //预留给数组实现方式的接口，目前无用
bool QUEUE<T>::ClearQueue()
{
    this->DestroyQueue();
    return true;
}

template <typename T> //获取第一个元素，不出队
T QUEUE<T>::getHead()
{
    if (length == 0)
        return false;
    return front->data;
}

template <typename T> //入队函数
bool QUEUE<T>::enQueue(T data)
{
    Item *temp = new Item;
    temp->data = data;
    temp->next = nullptr;

    if (length == 0)
    {
        front = temp;
        rear = temp;
        length++;
        return true;
    }
    rear->next = temp;
    rear = temp;
    length++;
    return true;
}

template <typename T>
T QUEUE<T>::deQueue()
{
    T data;
    Item *temp;
    if (length == 0)
        return false;
    data = front->data;
    temp = front;
    front = front->next;
    delete temp;
    length--;
    if (length == 0)
        rear = nullptr;
    return data;
}

int main()
{
    QUEUE<int> a(0);
    cout << a.deQueue();
    a.enQueue(1);
    a.enQueue(2);
    cout << a.getHead();
    system("pause");
}