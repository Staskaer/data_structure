#ifndef ADT_H
#define ADT_H

template <typename T>
class ADT
{
private:
    int length;
    struct Item
    {
        T data;
        Item *next;
    };
    Item *item;

public:
    ADT(T data);
    ADT()
    {
        item = new Item;
        length = 0;
        item->data = 0;
        item->next = nullptr;
    };
    bool listEmpty();
    bool clearList();
    T getElement(int serial);
    bool locateElement(T data);
    bool listInsert(int serial, T data);
    T listdelete(int serial);
    int listLength() { return length; };
    ~ADT() { this->clearList(); };
};

#endif