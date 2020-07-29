#pragma once
#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>

#define	CLOCKS_PER_SEC	((clock_t)1000)

//using namespace std;

/*
全字符串查找替换
src:源字符串，输入输出
old_str:被替换字符串，输入
new_str:替换的字符串，输入

函数返回值：被替换的次数
*/
size_t m_replace(std::string &src, const std::string &old_str, const std::string &new_str);

/*
复制n此str
str:源字符串，输入
n:复制的次数，输入

函数返回值：将str复制n此后的字符串
*/
std::string repeat(std::string str, const std::size_t n);

