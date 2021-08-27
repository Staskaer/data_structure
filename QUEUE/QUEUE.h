#ifndef QUEUE_H_
#define QUEUE_H_

template <typename T>
class QUEUE
{
private:
    struct Item
    {
        T data;
        Item *next;
    };
    Item *front,*rear;
    int length;

public:
    QUEUE()
    {
        length = 0;
        front = nullptr;
        rear = nullptr;
    };
    QUEUE(T data)
    {
        length = 1;
        rear = front = new Item;
        front->next = nullptr;
        front->data = data;
    };
    bool DestroyQueue();
    bool ClearQueue();
    ~QUEUE() { this->DestroyQueue(); };
    T getHead();
    bool enQueue(T data);
    T deQueue();
    int QueueLength() { return length; };
};
#endif