#include "STRING.h"
#include <cstring>
using std::cin;
using std::cout;
using std::endl;

STRING::STRING(const char *ch) //转换构造函数
{
    len = std::strlen(ch);
    str = new char[len + 1];
    std::strcpy(str, ch);
}

STRING::STRING(STRING &s) //复制构造函数
{

    len = s.len;
    str = new char[len + 1];

    std::strcpy(str, s.str);
}

bool STRING::ClaerSting() //实际上的析构函数
{
    delete[] str;
    len = 0;
    return true;
}

bool STRING::strEmpty() const //判断是否为空的一个函数
{
    return len == 0;
}

int STRING::strlen() const //返回字符串长度
{
    return len;
}

int STRING::strCompare(const STRING &s) const //比较字符串大小
{
    if (len == 0 || s.len == 0)
        return false;
    return std::strcmp(this->str, s.str) == 0;
}
int STRING::strCompare(const char *ch) const
{
    if (std::strlen(ch) == 0 || len == 0)
        return false;
    return std::strcmp(this->str, ch) == 0;
}

bool STRING::concat(const STRING &s) //将s拼接在原字符串后面
{
    len = len + s.len;
    char *temp = new char[len + 1];
    std::strcpy(temp, str);
    delete[] str;
    std::strcat(temp, s.str);
    str = temp;
    return true;
}

bool STRING::strInsert(int i, const STRING &s) //在第i个字符后插入字符
{
    if (i > len)
        return false;
    len = len + s.len;
    char *temp = new char[len + 1];
    std::strcpy(temp, str);
    *(temp + i) = '\0';
    std::strcat(temp, s.str);
    std::strcat(temp, (str + i));
    delete[] str;
    str = temp;
    return true;
}
bool STRING::strInsert(int i, const char *ch) //在第i个字符后插入字符的函数的重载
{
    STRING temp(ch);
    return this->strInsert(i, temp);
}

STRING STRING::subStr(int pos, int lens) const //寻找pos位置后的长度为lens的字串
{
    if (lens + pos > len)
    {
        STRING result;
        return result;
    }
    char *temp = new char[lens + 1];
    for (int i = 0; i < lens; i++)
    {
        *(temp + i) = *(str + i + pos);
    }
    *(temp + lens) = '\0';
    STRING result(temp);
    return result;
}

bool STRING::strDelete(int pos, int lens) //删除pos位置后的长度为lens的字串
{
    if (pos + lens > len)
        return false;
    len = len - lens;
    char *temp = new char[len + 1];
    for (int i = 0, j = 0; i < len + lens; i++)
    {
        if (i <= pos - 1 || i > pos + lens - 1)
        {
            *(temp + j) = *(str + i);
            j++;
        }
    }
    *(temp + len) = '\0';
    delete[] str;
    str = temp;
    return true;
}

bool STRING::replace(const STRING &rawed, const STRING &newed) //替换原字符串中所有rawed字符串为newed
{
    int pos, count = 0;
    while (pos = this->Index_pusu(rawed)) //需要Index函数作为支持，否则不能使用
    {
        this->strDelete(pos - 1, rawed.len);
        this->strInsert(pos - 1, newed);
        count++;
    }
    return count;
}
bool STRING::replace(const STRING &rawed, const char *newed)
{
    int pos, count = 0;
    while (pos = this->Index_pusu(rawed)) //需要Index函数作为支持，否则不能使用
    {
        this->strDelete(pos - 1, rawed.len);
        this->strInsert(pos - 1, newed);
        count++;
    }
    return count;
}
bool STRING::replace(const char *rawed, const STRING &newed)
{
    int pos, count = 0;
    while (pos = this->Index_pusu(rawed)) //需要Index函数作为支持，否则不能使用
    {
        this->strDelete(pos - 1, std::strlen(rawed));
        this->strInsert(pos - 1, newed);
        count++;
    }
    return count;
}
bool STRING::replace(const char *rawed, const char *newed)
{
    int pos, count = 0;
    while (pos = this->Index_pusu(rawed)) //需要Index函数作为支持，否则不能使用
    {
        this->strDelete(pos - 1, std::strlen(rawed));
        this->strInsert(pos - 1, newed);
        count++;
    }
    return count;
}

int STRING::Index_pusu(const STRING &match_, int pos) const //朴素匹配
{
    //此为朴素匹配模式
    STRING temp;
    for (int i = pos; i < (this->len - match_.len + 1); i++)
    {
        temp = this->subStr(i, match_.strlen());
        if (match_.strCompare(this->subStr(i, match_.strlen())))
            return i + 1;
    }
    return 0;
}
int STRING::Index_pusu_plus(const STRING &match_, int pos) const //朴素匹配的改进形式
{
    int r_l = this->strlen() + 1, m_l = match_.strlen() + 1; //match的长度
    char *raw = this->str;
    char *match = match_.str; //设置两个指向两个对象中字符串的指针
    for (int i = pos, j = 0; i < r_l && j < m_l;)
    {
        if (raw[i] == match[j])
        {
            i++;
            j++;
        }
        else
        {
            i = i - j + 1; //若出现不匹配的字符，则i退回到最开始字符，即i-j(两者同加减),再进一，从下一个开始匹配
            j = 0;
        }

        if (j == m_l - 1)
            return i - m_l + 2;
    }
    return 0;
}
int STRING::Index_KMP(const STRING &match_, int pos) const //KMP模式匹配
{
    int mat_len = match_.strlen() + 1; //match的长度
    int i = 0, j = -1, next[mat_len - 1] = {0};
    next[0] = -1;
    char *raw = this->str, *match = match_.str;
    //先计算next数组
    while (i < mat_len - 1)
    {
        if (j == -1 || match[i] == match[j])
        {
            i++;
            j++;
            next[i] = j;
        }
        else
        {
            j = next[j];
        }
    }
    //next数组获取完成
    i = pos;
    j = 0;
    while (i < this->len + 1 && j < mat_len)
    {
        if (j == -1 || raw[i] == match[j])
        //next中的首位或者是符合匹配
        //当next中出现首位时表示此匹配串匹配到的位置没有首尾能够衔接的部分
        //下一轮匹配的j要从头开始
        //由于j回溯之后要和raw[i]重新比较，故i不应回溯
        //所以当j回溯到next首位时，i也应该向后
        //所以next首位设置为-1，表示直接开始下一轮比较
        {
            i++;
            j++;
        }
        else
        {
            j = next[j]; //j回溯到合适的位置
        }

        if (j == mat_len - 1)
            return i - mat_len + 2; //返回位置，原理同上
    }
    return 0;
}
int STRING::Index_KMP_plus(const STRING &match_, int pos) const //KMP的改进算法
{
    int mat_len = match_.strlen() + 1; //match的长度
    int i = 0, j = -1, next[mat_len - 1] = {0};
    next[0] = -1;
    char *raw = this->str, *match = match_.str;
    //先计算next数组

    while (i < mat_len - 1)
    {
        if (j == -1 || match[i] == match[j])
        {
            i++;
            j++;
            if (match[i] != match[j])
                //改进主要体现在next数组上，增加一个比较
                //当匹配之后的下一个字符与前缀的下一个字符不相等
                //说明匹配到此就结束了，计入next数组
                next[i] = j;
            else
                //若相等，说明可以继续匹配，采用之前的前缀的next数组位置，可以减少不必要的回溯
                next[i] = next[j];
        }
        else
        {
            j = next[j];
        }
    }
    //next数组获取完成
    i = pos;
    j = 0;
    while (i < this->len + 1 && j < mat_len)
    {
        if (j == -1 || raw[i] == match[j])
        {
            i++;
            j++;
        }
        else
        {
            j = next[j]; //j回溯到合适的位置
        }

        if (j == mat_len - 1)
            return i - mat_len + 2; //返回位置，原理同上
    }
    return 0;
}

STRING &STRING::operator=(const STRING &s) //运算符重载
{
    len = s.len;
    str = new char[len + 1];
    std::strcpy(str, s.str);
    return *this;
}
STRING &STRING::operator=(const char *ch) //运算符重载
{
    len = std::strlen(ch);
    str = new char[len + 1];
    std::strcpy(str, ch);
    return *this;
}

std::ostream &operator<<(std::ostream &os, const STRING s) //cout的友元
{
    cout << s.str;
    return os;
}

int main()
{
    STRING a("aba");
    STRING b("pln");
    //STRING b("123");
    //STRING c("b");
    STRING d("ababc");
    cout << d.Index_KMP_plus(a);
    system("pause");
}
