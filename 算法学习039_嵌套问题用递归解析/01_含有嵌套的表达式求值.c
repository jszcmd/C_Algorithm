#define _CRT_SECURE_NO_WARNINGS

// 01. 含有嵌套的表达式求值
// 力扣测试链接: https://leetcode.cn/problems/basic-calculator-iii/
// 力扣测试连接是会员题目
// 牛客测试连接:https://www.nowcoder.com/practice/c215ba61c8b1443b996351df929dc4d4

// #############################################################################
// (一):使用数组实现的简单的栈
// #############################################################################

#include <string.h> // 使用strlen函数
#include <stdio.h>  // 使用NULL
#include <stdlib.h> // 使用malloc和free

// 这个两个宏定义成1都可以过.....
// 根据题目要求,栈的最大容量应该足够大以处理输入表达式,可以根据实际需求调整
// 这里假设表达式中数字和操作符的总数不会超过100,那么栈的容量设置为50/100即可
#define INT_STACK_SIZE 8  // 整型栈的最大容量
#define CHAR_STACK_SIZE 8 // 字符型栈的最大容量

// -------------------------------------------------------
// int类型的数据栈的实现
// -------------------------------------------------------

// 整型栈
typedef struct
{
    int *base; // 栈底指针,指向存储空间
    int size;  // 当前栈中元素个数
} IntStack;

// 初始化整型栈 - 创建并初始化一个整型栈结构的指针
IntStack *InitIntStack()
{
    IntStack *obj = (IntStack *)malloc(sizeof(IntStack)); // 分配栈结构体内存
    if (obj == NULL)
        return NULL;                                         // 内存分配失败检查
    obj->base = (int *)malloc(INT_STACK_SIZE * sizeof(int)); // 分配栈数据存储空间
    if (obj->base == NULL)
    {
        free(obj); // 如果数据空间分配失败,释放已分配的结构体
        return NULL;
    }
    obj->size = 0; // 初始化栈大小为0,表示空栈
    return obj;    // 返回创建的栈对象的指针
}

// 判断整型栈是否为空 - 检查栈中是否包含元素
int IsIntStackEmpty(IntStack *obj)
{
    return obj->size == 0; // 如果size为0,栈为空
}

// 获取整型栈顶元素,不弹出 - 查看栈顶元素但不移除
int GetIntTop(IntStack *obj)
{
    if (IsIntStackEmpty(obj))
    {
        return -1; // 栈空时返回-1表示错误;实际在操作的时候我们是不会让这种情况发生的
    }
    return obj->base[obj->size - 1]; // 返回栈顶元素(位于size-1位置)
}

// 整型栈入栈 - 将新元素压入栈顶
int PushInt(IntStack *obj, int value)
{
    obj->base[obj->size] = value; // 在当前位置存入新值
    obj->size++;                  // 栈大小增加,指向下一个空闲位置
    return 1;                     // 返回成功标志
}

// 整型栈出栈 - 移除并返回栈顶元素
int PopInt(IntStack *obj)
{
    if (IsIntStackEmpty(obj))
    {
        return -1; // 栈空时返回-1表示错误;实际在操作的时候我们是不会让这种情况发生的
    }
    obj->size--;                 // 栈大小减少,相当于移除栈顶元素
    return obj->base[obj->size]; // 返回被移除的元素
}

// 销毁整型栈 - 释放栈占用的所有内存资源
void DestroyIntStack(IntStack *obj)
{
    if (obj != NULL)
    {
        free(obj->base); // 先释放数据存储空间
        free(obj);       // 再释放栈结构体本身
    }
}

// -------------------------------------------------------
// char类型的操作字符栈的实现
// -------------------------------------------------------

// 字符型栈
typedef struct
{
    char *base; // 栈底指针
    char *top;  // 栈顶指针
    int size;   // 当前栈中元素个数
} CharStack;

// 初始化字符型栈 - 创建并初始化一个字符型栈结构
CharStack *InitCharStack()
{
    CharStack *obj = (CharStack *)malloc(sizeof(CharStack)); // 分配栈结构体内存
    if (obj == NULL)
        return NULL;                                            // 内存分配失败检查
    obj->base = (char *)malloc(CHAR_STACK_SIZE * sizeof(char)); // 分配栈数据存储空间
    if (obj->base == NULL)
    {
        free(obj); // 如果数据空间分配失败,释放已分配的结构体
        return NULL;
    }
    obj->top = obj->base; // 初始时栈顶指针指向栈底,表示空栈
    obj->size = 0;        // 栈元素个数为0
    return obj;           // 返回创建的栈对象
}

// 判断字符型栈是否为空 - 检查栈中是否包含字符元素
int IsCharStackEmpty(CharStack *obj)
{
    return obj->top == obj->base; // 如果top等于base,栈为空
}

// 获取字符型栈顶元素 - 查看栈顶字符但不移除
char GetCharTop(CharStack *obj)
{
    if (IsCharStackEmpty(obj))
    {
        return '\0'; // 栈空时返回空字符
    }
    return *(obj->top - 1); // 返回栈顶元素(top指针指向下一个空闲位置,所以实际栈顶在top-1)
}

// 字符型栈入栈 - 将新字符压入栈顶
int PushChar(CharStack *obj, char value)
{
    *(obj->top) = value; // 在top指向的位置存入字符
    obj->top++;          // top指针上移，指向下一个空闲位置
    obj->size++;         // 栈元素个数增加
    return 1;            // 返回成功标志
}

// 字符型栈出栈 - 移除并返回栈顶字符
char PopChar(CharStack *obj)
{
    if (IsCharStackEmpty(obj))
    {
        return '\0'; // 栈空时返回空字符
    }
    obj->top--;         // top指针下移，指向新的栈顶元素
    obj->size--;        // 栈元素个数减少
    return *(obj->top); // 返回被移除的字符
}

// 销毁字符型栈 - 释放字符栈占用的所有内存资源
void DestroyCharStack(CharStack *obj)
{
    if (obj != NULL)
    {
        free(obj->base); // 先释放数据存储空间
        free(obj);       // 再释放栈结构体本身
    }
}

// #############################################################################
// (二):表达式求值的实现
// #############################################################################
// 注意C语言没有字符串类型,字符串是以字符数组的形式存在的
// 使用C语言提交的时候,函数的先后顺序要注意,需要把被调用的函数放在调用函数的前面
// 注意:最后的函数名要改成solve,因为牛客网的测试代码是调用solve函数的

int where = 0; // 全局指针,记录递归处理字符串的位置

// 压栈函数:处理数字和操作符的入栈逻辑,考虑运算符优先级
void push(IntStack *number, CharStack *ops, int cur, char op)
{
    int n = number->size; // 获取当前数字栈的大小
    // 如果栈为空,或者栈顶是低优先级运算符(+,-),直接压栈
    if ((n == 0) || (GetCharTop(ops) == '+') || (GetCharTop(ops) == '-'))
    {
        PushInt(number, cur); // 将当前数字压入数字栈
        PushChar(ops, op);    // 将操作符压入操作符栈
    }
    else
    {
        // 栈顶是高优先级运算符(*,/),需要先计算再压栈
        int topNumber = PopInt(number); // 弹出栈顶数字
        char topOper = PopChar(ops);    // 弹出栈顶操作符
        if (topOper == '*')
        {
            PushInt(number, topNumber * cur); // 执行乘法运算并压入结果
        }
        else
        {
            PushInt(number, topNumber / cur); // 执行除法运算并压入结果
        }
        PushChar(ops, op); // 将新的操作符压入操作符栈
    }
}

// 最终计算函数:处理栈中剩余的低优先级加减运算
int compute(IntStack *number, CharStack *ops)
{
    int n = number->size;      // 获取数字栈的大小
    int ans = number->base[0]; // 初始化结果为第一个数字
    int i = 0;
    // 遍历处理所有的加减运算
    for (i = 1; i < n; i++)
    {
        char curOps = ops->base[i - 1]; // 获取对应的操作符
        // 根据操作符决定是加还是减
        ans += (curOps == '+' ? number->base[i] : -number->base[i]);
    }
    return ans; // 返回最终计算结果
}

// 递归计算核心函数:处理数字,运算符和括号
int calc(char *s, int i)
{
    int len = strlen(s);               // 获取字符串长度
    int cur = 0;                       // 当前累积的数字值
    IntStack *number = InitIntStack(); // 初始化数字栈
    CharStack *ops = InitCharStack();  // 初始化操作符栈

    // 遍历表达式，直到字符串结束或遇到右括号
    while ((i < len) && (s[i] != ')'))
    {
        // 处理数字字符
        if (s[i] >= '0' && s[i] <= '9')
        {
            cur = cur * 10 + (s[i] - '0'); // 构建多位数
            i++;                           // 移动到下一个字符
        }
        // 处理运算符
        else if (s[i] != '(')
        {
            push(number, ops, cur, s[i]); // 将当前数字和运算符压栈
            cur = 0;                      // 重置当前数字
            i++;                          // 移动到下一个字符
        }
        // 处理左括号,开启递归计算
        else
        {
            cur = calc(s, i + 1); // 递归计算括号内的表达式
            i = where + 1;        // 更新指针到右括号后的位置
        }
    }
    // 处理最后一个数字和结束运算
    push(number, ops, cur, '+'); // 压入最后一个数字和结束符
    where = i;                   // 更新全局指针位置

    int result = compute(number, ops); // 计算最终结果

    // 释放栈内存，避免内存泄漏
    DestroyIntStack(number);
    DestroyCharStack(ops);

    return result; // 返回计算结果
}

// 主入口函数:计算字符串表达式的值
int solve(char *s)
{
    where = 0;         // 重置全局指针
    return calc(s, 0); // 从字符串起始位置开始计算
}
