#ifndef STACK_H_
#define STACK_H_

template <typename T>
class STACK
{
private:
    int length;
    struct Item
    {
        T data;
        Item *next;
    };
    Item *top;

public:
    STACK()
    {
        top = nullptr;
        length = 0;
    };
    STACK(T data)
    {
        top = new Item;
        top->data = data;
        top->next = nullptr;
        length = 1;
    };
    bool DestroyStack();
    bool ClearStack();
    bool StackEmpty();
    T getTop()
    {
        if (length == 0)
            return false;
        return top->data;
    };
    bool push(T);
    T pop();
    ~STACK() { this->DestroyStack(); }
};
#endif