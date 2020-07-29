#pragma once
#include "m_string.h"
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

int main()
{
	ifstream fid;
	ofstream fid_out;
	char in_file[] = "jinpingmei_1.txt";
	char out_file[] = "jinpingmei_2.txt";
	string ptr = "������";//���滻�ַ���
	string rep = "ximenqing";//�滻�ַ���

	fid.open(in_file, ios::in | ios::binary | ios::ate);
	if (!fid)//�ж��ļ����Ƿ�����
	{
		cout << "fail to open the file " <<in_file<< endl;
		return -1;//�����׳��쳣��
	}

	clock_t start, finish;
	double cost = 0.0;

	char *str_buf;
	long size = fid.tellg();
	str_buf = new char[size + 1];
	memset(str_buf, 0, size + 1);
	fid.seekg(0, ios::beg);
	fid.read(str_buf, size);
	string str(str_buf);

	str = repeat(str, 10);//�ظ�10��

	start = clock();

	size_t replace_cnt = 0;
	replace_cnt = m_replace(str, ptr, rep);//�����滻
	cout << ptr << "�滻��" << replace_cnt << "��" << endl;
	finish = clock();
	cost = (double)(finish - start) / CLOCKS_PER_SEC;
	cout << "�����滻��ʱ��" << cost << "(s)" << endl;

	//����д���ļ�
	fid_out.open(out_file, ostream::out | ostream::binary);
	if (!fid_out)
	{
		cout << "fail to open the file:" << out_file<<endl;
		return -1;//�����׳��쳣��
	}

	int size_str = str.size();
	char* cname = (char*)malloc((size_str + 1) * sizeof(char));
	strcpy_s(cname, size_str + 1, str.c_str());//stringתchar*
	fid_out.write(cname, size_str);

	free(cname);
	fid.close();
	fid_out.close();
	return 0;
}