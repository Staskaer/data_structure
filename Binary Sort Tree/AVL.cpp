#include "AVL.h"
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

//先定义内置类的两个方法

//这是内置类的默认构造函数
template <typename T>
AVL<T>::Item::Item()
{
    bf = 0;
    rchild = nullptr;
    lchild = nullptr;
};

//这是内置类的构造函数
template <typename T>
AVL<T>::Item::Item(T data_)
{
    data = data_;
    lchild = nullptr;
    rchild = nullptr;
};

//以下未tree类的方法

//这是tree类的单值构造函数
template <typename T>
AVL<T>::AVL(T data)
{
    num = 1;
    head = new Item;
    head->data = data;
    head->key = 1;
    depth = 1;
    head->bf = 0;
};

//单值连续输入的构造方法
template <typename T>
AVL<T>::AVL()
{
    //这个函数首先给根节点赋值
    char ch;
    Item *temp;
    T data;
    bool flag;
    num = 0;
    printf("node nullptr ? ( '#' for nullptr ,other for data) : ");
    cin >> ch;
    if (ch == '#')
        temp = nullptr;
    else
    {
        printf("please enter data : ");
        cin >> data;
        num++;
        temp = new Item;
        temp->data = data;
        head = temp; //至此完成头节点赋值和准备工作

        do //给树赋值直到取消输入
        {
            flag = this->CreateNode();
        } while (flag);
    }
    //计算深度
    depth = this->TreeDepth();
    //计算bf
    this->bf(head);
};

//对某个结点生成子树，构造函数的接口函数（私有方法）
template <typename T>
bool AVL<T>::CreateNode()
{
    //用于单个结点的输入赋值
    char ch;
    Item *temp, *p;
    T data;
    printf("node nullptr ? ( '#' for nullptr ,other for data) : ");
    cin >> ch;
    if (ch == '#')
    {
        temp = nullptr;
        return false; //取消输入
    }
    else
    {
        printf("please enter data : ");
        cin >> data;
        num++;
        temp = new Item;
        temp->data = data; //先输入数据

        if (!this->searchNode(data, p, head, nullptr)) //若树中不存在则赋值（p为若存在时的父节点）
        {
            if (data < p->data)
                p->lchild = temp;
            else
                p->rchild = temp;
        }
        else
            printf("node already exists\n");
    }
    return true;
}

//列表传参赋值
template <typename T>
AVL<T>::AVL(T *data, int len)
{
    Item *temp = new Item;
    temp->data = data[0];
    head = temp;
    num = 1;
    for (int i = 1; i < len; i++)
    {
        this->InsertNode(data[i]);
    }
    this->bf(head);
}

//查找子树元素，成功返回指向元素的指针，否则返回指向父节点（私有方法）
template <typename T>
bool AVL<T>::searchNode(T data, Item *&p, Item *tree, Item *parent)
//参数说明：data为要查找元素，p为调用传入指针，tree为查找的子树，parent为子树的双亲结点
//若在整个树中查询则（data，p，head，nullptr）
{

    Item *temp = tree; //tree和parent同时为空则p也为空
    if (temp == nullptr)
    {
        p = parent;
        return false;
    }
    else if (data == tree->data) //查找成功
    {
        p = tree;
        return true;
    }
    else if (data < tree->data) //根据大小判断是查找哪边的子节点
        return this->searchNode(data, p, tree->lchild, tree);
    else
        return this->searchNode(data, p, tree->rchild, tree);
}

//查找子树元素，返回元素的父节点，并根据查找成功返回true或false
template <typename T>
bool AVL<T>::searchNodeP(T data, Item *&p, Item *tree, Item *parent)
{
    Item *temp = tree; //tree和parent同时为空则p也为空
    if (temp == nullptr)
    {
        p = parent;
        return false;
    }
    else if (data == tree->data) //查找成功
    {
        p = parent;
        return true;
    }
    else if (data < tree->data) //根据大小判断是查找哪边的子节点
        return this->searchNodeP(data, p, tree->lchild, tree);
    else
        return this->searchNodeP(data, p, tree->rchild, tree);
}

//删除结点
template <typename T>
bool AVL<T>::DeleteNode(T data)
{
    Item *temp, *p, *q, *s;
    if (this->searchNodeP(data, p, head, nullptr))
    {
        if (p->data > data) //左节点
        {
            temp = p->lchild;
            if (temp->lchild == nullptr && temp->rchild == nullptr) //叶子结点则将父节点对应位置置为null
            {
                p->lchild = nullptr;
                delete temp;
            }
            else if (temp->lchild == nullptr && temp->rchild != nullptr) //右节点不空，左节点空
            {
                p->lchild = temp->rchild;
                delete temp;
            }
            else if (temp->lchild != nullptr && temp->rchild == nullptr) //左节点不空，右节点空
            {
                p->lchild = temp->lchild;
                delete temp;
            }
            else //左右均不空
            {
                q = temp,
                s = temp->lchild;            //先转左
                while (s->rchild != nullptr) //再向右转到头（找到前驱结点）
                {
                    q = s;
                    s = s->rchild; //此时q为前驱结点的双亲结点
                }
                temp->data = s->data;
                if (q != temp)             //只要重接s的左结点即可（s仅有左结点了）
                    q->rchild = s->lchild; //这说明要删除结点的左结点还有右子节点（s有所移动）,重接到q的右节点上
                else
                    q->lchild = s->lchild; //这说明要删除结点的左结点没有右子节点（s没有移动）,重接到q的左节点上

                delete s;
            }
            num--;
            depth = this->TreeDepth();
            this->bf(head);
            return true;
        }
        else //右节点
        {
            temp = p->rchild;
            if (temp->lchild == nullptr && temp->rchild == nullptr)
            {
                p->rchild = nullptr;
                delete temp;
            }
            else if (temp->lchild == nullptr && temp->rchild != nullptr)
            {
                p->rchild = temp->rchild;
                delete temp;
            }
            else if (temp->lchild != nullptr && temp->rchild == nullptr)
            {
                p->rchild = temp->lchild;
                delete temp;
            }
            else
            {
                q = temp,
                s = temp->lchild;            //先转左
                while (s->rchild != nullptr) //再向右转到头（找到前驱结点）
                {
                    q = s;
                    s = s->rchild; //此时q为前驱结点的双亲结点
                }
                temp->data = s->data;
                if (q != temp)             //只要重接s的左结点即可（s仅有左结点了）
                    q->rchild = s->lchild; //这说明要删除结点的左结点还有右子节点（s有所移动）,重接到q的右节点上
                else
                    q->lchild = s->lchild; //这说明要删除结点的左结点没有右子节点（s没有移动）,重接到q的左节点上

                delete s;
            }
            num--;
            depth = this->TreeDepth();
            this->bf(head);
            return true;
        }
    }
    return false;
}

//插入新结点
template <typename T>
bool AVL<T>::InsertNode(T data)
{
    Item *p, *temp;
    if (!this->searchNode(data, p, head, nullptr))
    {
        temp = new Item;
        temp->data = data;
        num++;
        if (p->data > data)
            p->lchild = temp;
        else
            p->rchild = temp;
        depth = this->TreeDepth();
        return true;
    }
    return false;
}

//计算返回深度（私有方法）
template <typename T>
int AVL<T>::TreeDepth()
{
    int depth = 0;
    Item *temp = head;
    if (temp == nullptr)
        return depth;
    depth = this->maxdepth(temp);
    return depth;
}

//返回子树的最大深度（私有方法）
template <typename T>
int AVL<T>::maxdepth(Item *item)
{
    if (item == nullptr)
        return 0;
    else //返回左子树和右子树中最大的深度再加上自身的1
        return this->maxdepth(item->lchild) > this->maxdepth(item->rchild) ? this->maxdepth(item->lchild) + 1 : this->maxdepth(item->rchild) + 1;
}

//计算树的结点个数（私有方法）
template <typename T>
int AVL<T>::TreeNum()
{
    int num = 0;
    Item *temp = head;
    if (temp == nullptr)
        return num;
    num = this->count(temp);
    return num;
}

//返回子树的结点个数（私有方法）
template <typename T>
int AVL<T>::count(Item *item)
{
    if (item == nullptr)
        return 0;
    else
        return this->count(item->lchild) + this->count(item->rchild) + 1;
}

//返回深度
template <typename T>
int AVL<T>::Depth()
{
    return depth;
}

//归档时的方法
//为整树计算bf(私有方法)//用不到
template <typename T>
int AVL<T>::bf(Item *temp)
{
    //此函数在返回深度的基础上改的
    if (temp == nullptr)
        return 0;
    else //返回左子树和右子树中最大的深度再加上自身的1
    {
        int lh = 0, rh = 0;
        lh = this->bf(temp->lchild);
        rh = this->bf(temp->rchild);
        temp->bf = lh - rh;
        return lh > rh ? lh + 1 : rh + 1;
    }
}

//左旋（私有方法）//用不到
template <typename T>
typename AVL<T>::Item *AVL<T>::lspan(Item *&item)
{
    Item *temp = item->lchild;
    item->lchild = temp->rchild;
    temp->rchild = item;
    item = temp;
    return temp;
}

//右旋（私有方法）//用不到
template <typename T>
typename AVL<T>::Item *AVL<T>::rspan(Item *&item)
{
    Item *temp = item->rchild;
    item->rchild = temp->lchild;
    temp->lchild = item;
    item = temp;
    return temp;
}

//左平衡处理函数（私有方法）//用不了
template <typename T>
typename AVL<T>::Item *AVL<T>::lbalance(Item *&item)
{
    Item *l, *lr;
    l = item->lchild;
    switch (l->bf)
    {
    case 1: //插在左孩子左子树，要右旋
        item->bf = l->bf = 0;
        this->rspan(item);
        break;
    case -1: //插在左孩子右子树，双旋
        lr = l->rchild;
        switch (lr->bf)
        {
        case 1:
            l->bf = 0;
            break;
        case 0:
            item->bf = l->bf = 0;
            break;
        case -1:
            item->bf = 0;
            l->bf = 1;
            break;
        }
    }
    lr->bf = 0;
    this->lspan(l->lchild);
    this->rspan(item);
}

//右平衡处理函数（私有方法）//用不了
template <typename T>
typename AVL<T>::Item *AVL<T>::rbalance(Item *&item)
{
    Item *l, *lr;
    l = item->lchild;
    switch (l->bf)
    {
    case 1: //插在左孩子左子树，要右旋
        item->bf = l->bf = 0;
        this->rspan(item);
        break;
    case -1: //插在左孩子右子树，双旋
        lr = l->rchild;
        switch (lr->bf)
        {
        case 1:
            l->bf = 0;
            break;
        case 0:
            item->bf = l->bf = 0;
            break;
        case -1:
            item->bf = 0;
            l->bf = 1;
            break;
        }
    }
    lr->bf = 0;
    this->lspan(l->lchild);
    this->rspan(item);
}

int main()
{
    int list[] = {6, 8, 5, 1, 9, 4, 3, 7, 2, 0};
    AVL<int> a(list, 10);
    //a.InsertNode(10);
    //a.InsertNode(5);
    //a.DeleteNode(0);
    system("pause");
}