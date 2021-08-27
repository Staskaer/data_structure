#include "TREE.h"
#include <iostream>
#include <queue>
#include <stack>
using std::cin;
using std::cout;
using std::endl;
using std::queue;
using std::stack;

//先定义内置类的两个方法

//这是内置类的默认构造函数
template <typename T>
TREE<T>::Item::Item()
{
    key = -1;
    rchild = nullptr;
    lchild = nullptr;
};

//这是内置类的构造函数
template <typename T>
TREE<T>::Item::Item(T data_, int key_)
{
    data = data_;
    key = key_;
    lchild = nullptr;
    rchild = nullptr;
};

//以下未tree类的方法

//这是tree类的单值构造函数
template <typename T>
TREE<T>::TREE(T data)
{
    num = 1;
    head = new Item;
    head->data = data;
    head->key = 1;
    depth = 1;
}

//单值连续输入的构造方法
template <typename T>
TREE<T>::TREE()
{

    char ch;
    Item *temp;
    int key = 1;
    T data;
    num = 0;
    printf("node %d nullptr ? ( '#' for nullptr ,other for data) : ", key);
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
        temp->key = key;
        temp->lchild = this->CreateTree(key * 2); //某结点左子树的位置是此结点位置*2，右子树再加一
        temp->rchild = this->CreateTree(key * 2 + 1);
    }
    head = temp;
    depth = this->TreeDepth();
}

//对某个结点生成子树，构造函数的接口函数（私有方法）
template <typename T>
typename TREE<T>::Item *TREE<T>::CreateTree(int key)
{

    char ch;
    Item *temp;
    T data;
    printf("node %d nullptr ? ( '#' for nullptr ,other for data) : ", key);
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
        temp->key = key;
        temp->lchild = this->CreateTree(key * 2);
        temp->rchild = this->CreateTree(key * 2 + 1);
    }
    return temp;
}

//这是tree类的列表传参构造函数
template <typename T>
TREE<T>::TREE(T *list, int length)
{
    if (length <= 0)
        head = nullptr;
    //先构造出第一个根节点
    Item *fir = new Item;
    fir->data = list[0];
    fir->key = 1;
    num = 1;
    head = fir;

    //剩下个依次插入即可
    for (int i = 1; i < length; i++)
    {
        this->InsertNode(i + 1, list[i]);
    }
    depth = this->TreeDepth();
}

//在某位置插入结点,或更改指定结点
template <typename T>
bool TREE<T>::InsertNode(int pos, T data)
{
    //先获取双亲结点位置
    Item *parent = this->Node(pos / 2);
    if (parent == nullptr)
        return false;
    //再检查当前结点是否存在
    Item *self = this->Node(pos);
    //再根据位置信息插入结点,备份左右子节点
    Item *temp = new Item;
    if (pos % 2 == 0)
        parent->lchild = temp;
    else
        parent->rchild = temp;
    temp->data = data;
    temp->key = pos;
    if (self == nullptr) //添加结点才增加个数
        num++;
    if (self != nullptr)
    {
        temp->lchild = self->lchild;
        temp->rchild = self->rchild;
    }
    depth = this->TreeDepth();
    return true;
}

//获取某子树（默认根）的某位置的结点指针（私有方法）
template <typename T>
typename TREE<T>::Item *TREE<T>::Node(int pos, Item *item)
{
    if (pos <= 0)
        return nullptr;
    Item *pt, *temp = nullptr;
    if (item == nullptr)
        pt = head;
    else
        pt = item;

    //查找操作

    if (pt->key == pos)
        return pt;
    else
    {
        if (temp == nullptr && pt->lchild != nullptr)
            temp = this->Node(pos, pt->lchild); //不是根结点，左子树不空，查找左子树
        if (temp == nullptr && pt->rchild != nullptr)
            temp = this->Node(pos, pt->rchild); //不是左子树，右子树不空，查找右子树
    }
    return temp;
}

//判断是否未为空树
template <typename T>
bool TREE<T>::TreeNotEmpty()
{
    return num != 0;
}

//返回深度
template <typename T>
int TREE<T>::Deepth()
{
    return depth;
}

//计算返回深度（私有方法）
template <typename T>
int TREE<T>::TreeDepth()
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
int TREE<T>::maxdepth(Item *item)
{
    if (item == nullptr)
        return 0;
    else //返回左子树和右子树中最大的深度再加上自身的1
        return this->maxdepth(item->lchild) > this->maxdepth(item->rchild) ? this->maxdepth(item->lchild) + 1 : this->maxdepth(item->rchild) + 1;
}

//计算树的结点个数（私有方法）
template <typename T>
int TREE<T>::TreeNum()
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
int TREE<T>::count(Item *item)
{
    if (item == nullptr)
        return 0;
    else
        return this->count(item->lchild) + this->count(item->rchild) + 1;
}

//返回某位置结点的值
template <typename T>
T TREE<T>::Vuale(int pos)
{
    Item *temp = this->Node(pos);
    if (temp)
        return temp->data;
    return false;
}

//返回根节点数据
template <typename T>
T TREE<T>::Root()
{
    if (head)
        return head->data;
    return false;
}

//给某位置结点赋值
template <typename T>
bool TREE<T>::Assign(int pos, T data_)
{
    Item *temp = this->Node(pos);
    if (temp)
    {
        temp->data = data_;
        return true;
    }
    return false;
}

//返回双亲结点的数据
template <typename T>
T TREE<T>::Parent(int pos)
{
    Item *temp = this->Node(pos / 2);
    if (temp)
        return temp->data;
    return false;
}

//返回左节点数据
template <typename T>
T TREE<T>::LChild(int pos)
{
    Item *temp = Node(pos)->lchild;
    if (temp)
        return temp->data;
    return false;
}

//返回右节点数据
template <typename T>
T TREE<T>::RChild(int pos)
{
    Item *temp = Node(pos)->rchild;
    if (temp)
        return temp->data;
    return false;
}

//删除某节点及其所有子节点
template <typename T>
bool TREE<T>::DeleteNode(int pos)
{
    Item *temp = this->Node(pos);
    if (temp)
    {
        if (temp->lchild != nullptr)
            this->DeleteNode(temp->lchild->key);
        if (temp->rchild != nullptr)
            this->DeleteNode(temp->rchild->key);

        //释放自身及子节点之前要设置父节点的对应的指针为nullptr
        Item *parent = this->Node((temp->key) / 2);
        if (parent)
        {
            if ((temp->key) % 2 == 0)
                parent->lchild = nullptr;
            else
                parent->rchild = nullptr;
        }
        delete temp;
        depth = this->TreeDepth();
        num = this->TreeNum();
        return true;
    }
    return false;
}

//pop某结点
template <typename T>
T TREE<T>::POPNode(int pos)
{
    Item *temp = this->Node(pos);
    T data = temp->data;
    if (this->DeleteNode(pos))
        return data;
    return false;
}

//返回右兄弟结点
template <typename T>
T TREE<T>::RightSibling(int pos)
{
    Item temp = this->Node(pos + 1);
    if (temp)
        return temp->data;
    return false;
}

//析构函数
template <typename T>
TREE<T>::~TREE()
{
    this->DeleteNode(1);
}

//前序遍历的递归算法
template <typename T>
void TREE<T>::qianxu_d()
{
    Item *temp = head;
    if (temp)
        this->qianxu_d_s(temp);
}

//前序遍历的实际递归函数（私有方法）
template <typename T>
void TREE<T>::qianxu_d_s(Item *temp)
{
    if (temp != nullptr)
        cout << temp->data << endl;
    if (temp->lchild != nullptr)
        this->qianxu_d_s(temp->lchild);
    if (temp->rchild != nullptr)
        this->qianxu_d_s(temp->rchild);
}

//前序遍历非递归实现
template <typename T>
void TREE<T>::qianxu_f()
{
    Item *temp = head;
    if (temp)
    {
        stack<Item *> s;
        while (!s.empty() || temp != nullptr) //当前子树不空或栈不空
        {
            while (temp != nullptr)
            {
                cout << temp->data << endl;
                s.push(temp);        //将结点入栈
                temp = temp->lchild; //继续遍历左子树直到完成
            }

            if (!s.empty())
            {
                temp = s.top();
                s.pop();
                temp = temp->rchild; //转至右子树
            }
        }
    }
}

//层序遍历（高复杂度）
template <typename T>
void TREE<T>::cengxu()
{
    for (int i = 1; i <= num; i++)
    {
        Item *temp = this->Node(i);
        if (temp)
            cout << temp->data << endl;
    }
}

//层序遍历的队列实现法
template <typename T>
void TREE<T>::cengxu_q()
{
    Item *temp = head;
    if (temp)
    {
        queue<Item *> q;
        q.push(temp);
        while (!q.empty())
        {
            temp = q.front();
            cout << temp->data << endl;
            q.pop();
            if (temp->lchild != nullptr)
                q.push(temp->lchild);
            if (temp->rchild != nullptr)
                q.push(temp->rchild);
        }
    }
}

//测试私有方法的接口
template <typename T>
void TREE<T>::test()
{
    //Item *temp = this->Node(3);
}

int main()
{
    int list[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    TREE<int> a(list, 8);

    a.InsertNode(2, 2);
    a.InsertNode(5, 5);
    a.InsertNode(3, 3);
    a.InsertNode(7, 7);
    a.InsertNode(14, 14);
    a.InsertNode(2, 10);

    //a.cengxu_q();
    //cout << endl;
    //a.qianxu_d();
    system("pause");
}