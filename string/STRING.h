#ifndef STRING_H_
#define STRING_H_
#include <iostream>
class STRING
{
private:
    char *str;
    int len;

public:
    STRING()
    {
        str = nullptr;
        len = 0;
    };
    STRING(const char *); //转换构造函数
    STRING(STRING &);     //复制构造函数

    bool strEmpty() const;
    int strlen() const;

    int strCompare(const STRING &) const;
    int strCompare(const char *) const;
    bool concat(const STRING &);

    int Index_pusu(const STRING &, int pos = 0) const;      //最简单的朴素匹配
    int Index_pusu_plus(const STRING &, int pos = 0) const; //朴素匹配的改进形式
    int Index_KMP(const STRING &, int pos = 0) const;       //KMP模式匹配算法
    int Index_KMP_plus(const STRING &, int pos = 0) const;  //KMP模式匹配的改进算法

    bool strInsert(int, const STRING &);
    bool strInsert(int, const char *);
    bool strDelete(int, int);

    STRING subStr(int, int) const;

    bool replace(const STRING &, const STRING &);
    bool replace(const char *, const char *);
    bool replace(const char *, const STRING &);
    bool replace(const STRING &, const char *);

    bool ClaerSting();
    ~STRING() { this->ClaerSting(); };

    STRING &operator=(const STRING &);
    STRING &operator=(const char *);
    friend std::ostream &operator<<(std::ostream &, const STRING); //重载的友元
};
#endif