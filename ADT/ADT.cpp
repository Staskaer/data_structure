#include "ADT.h"
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

template <typename T> //构造函数
ADT<T>::ADT(T data)
{
    length = 1;
    item = new Item;
    item->data = data;
    item->next = nullptr;
}

template <typename T> //返回ADT是否为空
bool ADT<T>::listEmpty()
{
    return length == 0;
}

template <typename T> //删除ADT
bool ADT<T>::clearList()
{
    Item *start = item, *temp;
    if (start->next == nullptr)
    {
        delete start;
        return true;
    }

    while (start->next != nullptr)
    {
        temp = start->next;
        delete start;
        start = temp;
    }
    return true;
}

template <typename T> //获取第i位置元素
T ADT<T>::getElement(int serial)
{
    if (serial > length)
        return false;
    Item *start = item;
    for (int i = 1; i < serial; i++)
        start = start->next;
    return start->data;
}

template <typename T> //判断data是否在ADT中
bool ADT<T>::locateElement(T data)
{
    if (this->listEmpty())
        return false;
    do
    {
        if (item->data == data)
            return true;
    } while (item->next != nullptr);
    return false;
}

template <typename T> //在serial处插入data元素
bool ADT<T>::listInsert(int serial, T data)
{
    Item *temp = new Item;
    Item *p = item;

    if (length == 0 && serial == 1)
    {
        item->data = data;
        length++;
        return true;
    }

    for (int i = 1; i < serial; i++)
    {
        if (p->next != nullptr)
            p = p->next;
        else
            return false;
    }

    temp->next = p->next;
    p->next = temp;
    temp->data = data;
    length++;
    return true;
}

template <typename T> //删除第serial项
T ADT<T>::listdelete(int serial)
{
    if (serial > length)
        return false;
    Item *p = item, *temp;
    T data;
    if (serial == 1)
    {
        if (this->listEmpty())
            return false;
        item = p->next;
        data = p->data;
        delete p;
        return data;
    }

    for (int i = 1; i < serial; i++)
    {
        if (p->next != nullptr)
        {
            temp = p;
            p = p->next;
        }
        else
            return false;
    };
    data = p->data;
    temp->next = p->next;
    delete p;
    length--;
    return data;
}

int main()
{
    ADT<int> a;
    cout << a.listInsert(1, 2) << endl;
    //cout << a.getElement(2);
    a.listInsert(1, 3);
    a.listInsert(2, 4);
    cout << a.listdelete(1);
    system("pause");
}