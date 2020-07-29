#define _CRT_SECURE_NO_WARNINGS

#include "m_string.h"

size_t m_replace(std::string &src, const std::string &old_str, const std::string &new_str)
{
	size_t replace_cnt = 0;//���ҵ����ж��ٴ���ͬ

	if (old_str.length() == 0||src.length()==0)
		return replace_cnt;

	//���з�����
	std::string _old_str;
	if (old_str == "\n")
		_old_str = "\r\n";//Windowsϵͳ����ĩ�����\r\n
	else
		_old_str = old_str;

	const size_t len_ptr = _old_str.length();//���滻�ַ������ֽڳ���
	const size_t len_new_str = new_str.length();//�滻�ַ����ĳ���
	const size_t len_src = src.length();//Դ�ַ����ó���

	std::vector<size_t> indexs;
	size_t index = 0;
	index = src.find(_old_str, index);
	if (index == std::string::npos)//û���ҵ������滻�ַ����������ؿ�ָ��
		return replace_cnt;

	//����λ��
	for (; index != std::string::npos;)
	{
		indexs.push_back(index);
		index = src.find(_old_str, index + len_ptr);
	}

	replace_cnt = indexs.size();//���ҵ����ж��ٴ���ͬ
	size_t new_vol = len_src + (len_new_str - len_ptr)*replace_cnt;//�´��ĳ���
	char *r_str;//�滻������ַ���
	r_str = (char*)malloc(new_vol + 1);//��һ����Ϊ����\0
	memset(r_str, 0, new_vol + 1);

	size_t start_index1 = 0;//��λԴ��
	size_t start_index2 = 0;//��λ�´�
	size_t r = 0;
	size_t count = 0;
	std::string substr;

	if (len_new_str == 0)//�滻�ַ�������Ϊ0ʱ����ɾ�����滻��
	{
		for (long i = 0; i < replace_cnt; i++)//ÿһ��ѭ����r��ʾ���ҵ���λ��
		{
			r = indexs[i];
			count = r - start_index1;
			substr = src.substr(start_index1, count);
			start_index1 = r + len_ptr;//����Դ����λ
			strcpy_s(r_str + start_index2, count + 1, substr.c_str());//����
			start_index2 = start_index2 + count;//�����´���λ
		}
		substr = src.substr(start_index1);
		strcpy_s(r_str + start_index2, (len_src - start_index1) + 1, substr.c_str());//����
	}
	else//���滻�ַ�����Ϊ0ʱ
	{
		//��stringתΪchar*
		char* new_chars;
		new_chars = (char*)malloc(len_new_str + 1);
		memset(new_chars, 0, len_new_str + 1);
		strcpy_s(new_chars, len_new_str + 1, new_str.c_str());

		for (long i = 0; i < replace_cnt; i++)//ÿһ��ѭ����r��ʾ���ҵ���λ��
		{
			r = indexs[i];
			count = r - start_index1;
			substr = src.substr(start_index1, count);
			start_index1 = r + len_ptr;//����Դ����λ
			strcpy_s(r_str + start_index2, count + 1, substr.c_str());//����
			start_index2 = start_index2 + count;//�����´���λ
			strcpy_s(r_str + start_index2, len_new_str + 1, new_chars);//�滻
			start_index2 = start_index2 + len_new_str;//�ڶ��θ����´���λ
		}
		substr = src.substr(start_index1);
		strcpy_s(r_str + start_index2, (len_src - start_index1) + 1, substr.c_str());//����
		//����β��
		free(new_chars);
	}

	src.reserve(new_vol);
	src.replace(0, len_src, r_str);//���滻����ַ������ǵ�Դ�ַ���
	free(r_str);
	return replace_cnt;
}

std::string repeat(std::string str, const std::size_t n)
{
	if (n == 0) {
		str.clear();
		str.shrink_to_fit();
		return str;
	}
	else if (n == 1 || str.empty()) {
		return str;
	}
	const auto period = str.size();
	if (period == 1) {
		str.append(n - 1, str.front());
		return str;
	}
	str.reserve(period * n);
	std::size_t m{ 2 };
	for (; m < n; m *= 2) str += str;
	str.append(str.c_str(), (n - (m / 2)) * period);
	return str;
}