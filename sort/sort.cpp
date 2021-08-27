#include <iostream>
using namespace std;

void straight_insert(int *p, int len); //直接插入排序

void jishu(int *p, int len, int max, int min); //计数排序

void xier(int *p, int len); //希尔排序

void heapsort(int *p, int len);         //堆排序
void heap_adjust(int *p, int s, int m); //堆调整

void mergesort(int *p, int len);                   //归并排序的外封装函数
void msort(int *sr, int *tr1, int s, int t);       //归并排序的递归实现法
void merge(int *sr, int *tr, int i, int m, int n); //归并

void mergesort2(int *p, int len);               //归并排序非递归实现的入口函数
void mergepass(int *sr, int *tr, int s, int n); //非递归归并排序用到的合并函数

void qsort(int *p, int len); //快速排序的封装函数

void qsort_d(int *p, int low, int high);     //快速排序递归实现
int partition_dc(int *p, int low, int high); //计算pivot（一个比较麻烦的双边实现）
int partition_d(int *p, int low, int high);  //计算pivot（双边循环的优化）
int partition_s(int *p, int low, int high);  //计算pivot（单边循环）

void qsort_f(int *p, int low, int high); //快速排序尾递归优化

int main()
{
    int a[7] = {5, 3, 6, 7, 4, 2, 1};
    qsort(a, 7);
    system("pause");
}

void straight_insert(int *p, int len) //直接插入排序
{
    int i, j, flag;
    for (i = 1; i < len; i++)
    {
        if (p[i - 1] > p[i]) //前比后大
        {
            flag = p[i];
            for (j = i - 1; p[j] > flag; j--) //插入到合适的位置
                p[j + 1] = p[j];
            p[j + 1] = flag;
            //要点是：flag设置为当前要处理的数字
            //内层for循环将处理数字插入到合适的位置：
            //同时兼顾比其小和比其大的数字，由for的条件控制
        }
    }
}

void jishu(int *p, int len, int max, int min) //计数排序
{
    const int num = max - min + 1;
    int *b = new int[num];
    for (int i = 0; i < len; i++)
        b[p[i]] = p[i];
    for (int i = 0; i < num; i++)
        if (b[i] != 0)
            printf("%d", b[i]);
    delete[] b;
}

void xier(int *p, int len) //希尔排序
{
    int i, j, increment = len, flag;
    do
    {
        increment = increment / 3 + 1; //起始分隔子序列的参数
        for (i = increment; i < len; i++)
        {
            if (p[i] < p[i - increment]) //子序列的前者大
            {
                flag = p[i];
                for (j = i - increment; j >= 0 && flag < p[j]; j -= increment) //像插入排序那样移动,不同的是希尔排序的子序列长度不定
                    p[j + increment] = p[j];
                p[j + increment] = flag;
            }
        }
    } while (increment > 1);
}

void heapsort(int *p, int len) //堆排序
{
    int i, temp;
    for (i = (len - 1) / 2; i >= 0; i--) //这个构建的几个参数要从堆的结构上理解，从（len-1）/2开始是为了从有孩子结点的结点开始
        heap_adjust(p, i, len - 1);      //这个函数是将[i,len]的结点中除i外结点是堆的p构建成堆（从最后一个有子孩子的结点开始也满足

    for (i = len - 1; i >= 0; i--) //每次将无序的最后一位与堆顶交换，再重新构建堆
    {
        temp = p[0];
        p[0] = p[i];
        p[i] = temp;
        heap_adjust(p, 0, i - 1);
    }
}

void heap_adjust(int *p, int s, int m) //堆调整
{
    //若p[s...m]中除s外均符合堆定义，此函数调整p[s...m]中s的位置，使得整个序列符合堆定义
    //传入的s，m均是合法的地址，也是需要处理的数值的地址，不要用<而用<=
    //是从上至下的比较顶点的值
    int temp, j;
    temp = p[s];
    for (j = 2 * s + 1; j <= m; j = 2 * j + 1) //这是从左孩子开始
    {
        if (j < m && p[j] < p[j + 1]) //逻辑右孩子比较大 记录下右孩子坐标
            j++;
        if (temp > p[j]) //最顶点比最大子孩子还要大,此时s不用变动
            break;
        p[s] = p[j]; //否则将现在的顶点置为最大的子孩子数值
        s = j;       //并记录应该插入的位置，即为刚才最大子孩子的位置
    }
    p[s] = temp; //统一的插入操作
}

void mergesort(int *p, int len) //归并排序的接口函数
{
    msort(p, p, 0, len - 1);
}

void msort(int sr[], int tr1[], int s, int t) //归并排序的递归实现法
{
    //将sr[s...t]排序为tr[s...t]，s和t均为合法下标
    int m;
    int tr2[t - s + 1]; //计算出数组长度并分配内存
    if (s == t)
        tr1[s] = sr[s];
    else
    {
        m = (s + t) / 2; //分隔数组，开始归并排序
        msort(sr, tr2, s, m);
        msort(sr, tr2, m + 1, t); //将sr的序列分别排序到tr中
        merge(tr2, tr1, s, m, t); //将tr2中的两段序列归并到tr1
    }
}

void merge(int sr[], int tr[], int i, int m, int n) //归并
{
    //将有序的sr[i...m]和sr[m+1...n]归并到tr1[i...n]，均为合法下标
    int j, k, l;
    for (j = m + 1, k = i; i <= m && j <= n; k++) //两个数组比较者小的先入
    {
        if (sr[i] < sr[j])
            tr[k] = sr[i++];
        else
            tr[k] = sr[j++];
    }

    //当有一个数组先排完了剩下的顺次进去就行了
    if (i <= m)
        for (l = 0; l < m - i + 1; l++)
            tr[k + l] = sr[i + l];

    if (j <= n)
        for (l = 0; l < n - j + 1; ++l)
            tr[k + l] = sr[j + l];
}

void mergesort2(int *p, int len)
{
    int *tr = new int[len];
    int k = 1;
    while (k < len)
    {
        mergepass(p, tr, k, len - 1); //将原序列中相邻长度为k的小单元合并到tr，合并后最小块长度为2k
        k = k * 2;
        mergepass(tr, p, k, len - 1); //将合并后的小序列重新按照长度为k回到p中，合并后最小块长度为2k
        k = k * 2;
        //注意，k始终为数值长度，而非小序列长度
        //非递归直接从最小的2个块开始向上合并
    }
}

void mergepass(int *sr, int *tr, int s, int n)
{
    //将2s个相邻块合并到tr
    int i = 0;
    int j;
    while (i <= n - 2 * s + 1) //先将能够分成两个k块的组的两两的归并
    {
        merge(sr, tr, i, i + s - 1, i + 2 * s - 1);
        i = 2 * s + i;
    }
    if (i < n - s + 1)                  //如果出现单独的不符合分组的块
        merge(sr, tr, i, i + s - 1, n); //自个排：如果还能分出一个k块出来就分成一个k块和剩下的
    else
        for (j = i; j <= n; j++) //分不出来就i直接加进去，不管它，反正最终也能分出一个k块+剩下的那种情况
            tr[j] = sr[j];
}

void qsort(int *p, int len)
{
    qsort_f(p, 0, len - 1);
}

void qsort_d(int *p, int low, int high)
{
    int pivot;
    if (low < high)
    {
        pivot = partition_s(p, low, high);
        qsort_d(p, low, pivot - 1); //分而治之
        qsort_d(p, pivot + 1, high);
    }
}

int partition_dc(int *p, int low, int high)
{
    //这是一个比较麻烦的双边实现
    int pivotkey = p[low], temp, flag = 0;
    while (low < high)
    {
        //注意，开始的时候，low指向的是pivot
        //所以每次交换实际上也是对pivot的实际元素进行交换

        while (low < high) //当high指向的元素比pivot大则停止移动high
            if (p[high] >= pivotkey)
                high--; //右边全是比pivot大的
            else
            {
                flag = 1;
                break;
            }

        if (flag)
        {
            temp = p[low];
            p[low] = p[high];
            p[high] = temp; //把pivot元素和小的交换一下，让实际上比较大的pivot在右边
            flag = 0;
        }

        while (low < high) //同上
            if (p[low] <= pivotkey)
                low++;
            else
            {
                flag = 1;
                break;
            }

        if (flag)
        {
            temp = p[low];
            p[low] = p[high];
            p[high] = temp; //把pivot元素和小的交换一下，让实际上比较大的pivot在右边
            flag = 0;
        }
    }
    return low;
}

int partition_d(int *p, int low, int high)
{
    int pivotkey = p[low], temp; //首位作为pivot
    while (low < high)
    {
        while (low < high && p[high] > pivotkey)
            high--;
        while (low < high && p[low] < pivotkey)
            low++;
        if (low < high) //优化了交换次数，每次交换不直接操作pivot元素
        {
            temp = p[low];
            p[low] = p[high];
            p[high] = temp;
        }
    }
    return low;
}

int partition_s(int *p, int low, int high)
{
    //单边实现代码更加简洁
    int pivotkey = p[low], temp, mark = low;
    for (int i = low + 1; i <= high; i++)
    {
        if (p[i] < pivotkey) //当遇到比pivot小的元素就先把mark指针右移，然后两者交换
        {
            mark++; //实际上就是划分出一个比pivot小的区域，这个区域由mark标识
            temp = p[i];
            p[i] = p[mark];
            p[mark] = temp;
        }
    }

    p[low] = p[mark];
    p[mark] = pivotkey; //最后把pivot移动到分界线上
    return mark;
}

void qsort_f(int *p, int low, int high)
{
    int pivot;
    while (low < high)
    {
        pivot = partition_s(p, low, high);
        qsort_f(p, low, pivot - 1);
        low = pivot + 1;
    }
}