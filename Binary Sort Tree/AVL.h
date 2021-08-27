#ifndef AVL_H_
#define AVL_H_

template <typename T>
class AVL
{
private:
    class Item
    {
    public:
        int bf; //这个用于存储平衡因子

        T data;
        Item *rchild, *lchild;
        Item();
        Item(T data_);
    };

    Item *head;
    int num;
    int depth;

    //以下是私有方法
    bool CreateNode();                            //对某个结点生成子树
    int TreeNum();                                //计算树的结点个数
    int TreeDepth();                              //计算TREE的深度
    int maxdepth(Item *);                         //获取子树的最大深度
    int count(Item *);                            //返回子节点的个数
    bool searchNode(T, Item *&, Item *, Item *);  //查找子树元素，成功返回指向元素的指针，否则返回指向父节点
    bool searchNodeP(T, Item *&, Item *, Item *); //查找子树元素，返回元素的父节点，并根据查找成功返回true或false
    //可以用但是用不到的方法
    int bf(Item *);       //为整树计算bf
    Item *rspan(Item *&); //bf为正时的右旋
    Item *lspan(Item *&); //bf为负时的左旋
    //用不了的方法(未实现，或者没有测试)
    Item *lbalance(Item *&); //左平衡处理函数
    Item *rbalance(Item *&); //右平衡处理函数
    bool Insert_avl(T);      //平衡插入
    bool bal_init(Item *);   //整树平衡化接口

public:
    AVL();              //默认的构造函数采用每个输入的方式
    AVL(T data);        //构造单个数据
    AVL(T *, int);      //数组传参来构造
    ~AVL(){};           //析构函数
    bool InsertNode(T); //插入新节点
    int Depth();        //返回深度
    bool DeleteNode(T); //删除结点
    //关键方法
    //排序化(排序化应该在构建的时候实现)(done!)
    //平衡化
    //平衡化依赖于获取子树深度的方法
};

#endif

//当前进度是实现了二叉排序树，包括插入和删除等操作
//本来想在排序树的基础上增加平衡化
//但是平衡树应该是从插入结点开始的
//所以现在打算修改以下插入的算法，取消最终平衡化的过程
//但是将保留这个接口

//8.22更新：
//平衡化的方法太扯了，难以实现，
//归档了，就到排序树为止了