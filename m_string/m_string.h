#pragma once
#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>

#define	CLOCKS_PER_SEC	((clock_t)1000)

//using namespace std;

/*
ȫ�ַ��������滻
src:Դ�ַ������������
old_str:���滻�ַ���������
new_str:�滻���ַ���������

��������ֵ�����滻�Ĵ���
*/
size_t m_replace(std::string &src, const std::string &old_str, const std::string &new_str);

/*
����n��str
str:Դ�ַ���������
n:���ƵĴ���������

��������ֵ����str����n�˺���ַ���
*/
std::string repeat(std::string str, const std::size_t n);

