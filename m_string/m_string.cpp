#define _CRT_SECURE_NO_WARNINGS

#include "m_string.h"

size_t m_replace(std::string &src, const std::string &old_str, const std::string &new_str)
{
	size_t replace_cnt = 0;//查找到的有多少处相同

	if (old_str.length() == 0||src.length()==0)
		return replace_cnt;

	//换行符处理
	std::string _old_str;
	if (old_str == "\n")
		_old_str = "\r\n";//Windows系统中行末标记是\r\n
	else
		_old_str = old_str;

	const size_t len_ptr = _old_str.length();//被替换字符串的字节长度
	const size_t len_new_str = new_str.length();//替换字符串的长度
	const size_t len_src = src.length();//源字符串得长度

	std::vector<size_t> indexs;
	size_t index = 0;
	index = src.find(_old_str, index);
	if (index == std::string::npos)//没有找到，被替换字符串，并返回空指针
		return replace_cnt;

	//查找位置
	for (; index != std::string::npos;)
	{
		indexs.push_back(index);
		index = src.find(_old_str, index + len_ptr);
	}

	replace_cnt = indexs.size();//查找到的有多少处相同
	size_t new_vol = len_src + (len_new_str - len_ptr)*replace_cnt;//新串的长度
	char *r_str;//替换后的新字符串
	r_str = (char*)malloc(new_vol + 1);//加一是因为最后的\0
	memset(r_str, 0, new_vol + 1);

	size_t start_index1 = 0;//定位源串
	size_t start_index2 = 0;//定位新串
	size_t r = 0;
	size_t count = 0;
	std::string substr;

	if (len_new_str == 0)//替换字符串长度为0时，即删除被替换串
	{
		for (long i = 0; i < replace_cnt; i++)//每一次循环的r表示查找到的位置
		{
			r = indexs[i];
			count = r - start_index1;
			substr = src.substr(start_index1, count);
			start_index1 = r + len_ptr;//更新源串定位
			strcpy_s(r_str + start_index2, count + 1, substr.c_str());//复制
			start_index2 = start_index2 + count;//更新新串定位
		}
		substr = src.substr(start_index1);
		strcpy_s(r_str + start_index2, (len_src - start_index1) + 1, substr.c_str());//复制
	}
	else//当替换字符串不为0时
	{
		//将string转为char*
		char* new_chars;
		new_chars = (char*)malloc(len_new_str + 1);
		memset(new_chars, 0, len_new_str + 1);
		strcpy_s(new_chars, len_new_str + 1, new_str.c_str());

		for (long i = 0; i < replace_cnt; i++)//每一次循环的r表示查找到的位置
		{
			r = indexs[i];
			count = r - start_index1;
			substr = src.substr(start_index1, count);
			start_index1 = r + len_ptr;//更新源串定位
			strcpy_s(r_str + start_index2, count + 1, substr.c_str());//复制
			start_index2 = start_index2 + count;//更新新串定位
			strcpy_s(r_str + start_index2, len_new_str + 1, new_chars);//替换
			start_index2 = start_index2 + len_new_str;//第二次更新新串定位
		}
		substr = src.substr(start_index1);
		strcpy_s(r_str + start_index2, (len_src - start_index1) + 1, substr.c_str());//复制
		//复制尾部
		free(new_chars);
	}

	src.reserve(new_vol);
	src.replace(0, len_src, r_str);//用替换后的字符串覆盖掉源字符串
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