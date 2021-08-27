#ifndef TREE_H_
#define TREE_H

template <typename T>
class TREE
{
private:
    class Item
    {
    public:
        T data;
        int key;
        Item *rchild, *lchild;
        Item();
        Item(T data_, int key_ = -1);
    };

    Item *head;
    int num;
    int depth;

    //以下为私有方法

    Item *CreateTree(int);                         //对某个结点生成子树
    Item *Node(int pos = 1, Item *item = nullptr); //返回某位置结点的指针，是从对象调用的方法
    int maxdepth(Item *);                          //获取子树的最大深度
    int TreeDepth();                               //计算TREE的深度
    int TreeNum();                                 //计算树的结点个数
    int count(Item *);                             //返回子节点的个数
    void qianxu_d_s(Item *);                       //前序遍历的递归

public:
    TREE();         //默认的构造函数采用每个输入的方式
    TREE(T data);   //构造单个数据
    TREE(T *, int); //数组传参来构造
    ~TREE();        //析构函数

    bool DestoryTree() //默认调用析构函数的接口
    {
        this->~TREE();
        return true;
    };

    bool TreeNotEmpty();     //返回是否为空树
    int Deepth();            //返回深度
    T Vuale(int);            //返回某位置的数据
    T Root();                //返回头节点数据
    bool Assign(int, T);     //将某位置的结点赋值
    T Parent(int);           //返回双亲数据
    T LChild(int);           //返回某位置的左节点数据
    T RChild(int);           //返回某位置的右节点数据
    T RightSibling(int);     //返回右兄弟结点
    bool InsertNode(int, T); //在某位置插入结点
    bool DeleteNode(int);    //删除某位置的结点
    T POPNode(int);          //将某节点采用POP的操作

    void test(); //测试用接口函数

    //还有一些便利的操作没有纳入，以后有时间再写
    void qianxu_d(); //前序遍历,递归实现
    void qianxu_f(); //前序遍历的非递归
    void cengxu();   //层序遍历，高复杂度
    void cengxu_q(); //利用队列实现的层序遍历
};

#endif