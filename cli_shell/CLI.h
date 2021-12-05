#pragma once
#ifndef __CLI
#define __CLI
#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include <sstream>
#include <algorithm>
#include <functional>
#include <cctype>
#include <typeinfo>
class CLI
{
public:
	CLI();
	~CLI();

	struct dir
	{
		std::string parent_title;
		std::string dir_title;
		std::vector<std::tuple<std::string, std::function<void()>, int, std::string>> com_list;
	};

	struct commands
	{
		std::string title;
		std::function<void()> func;
		int argsize;
		std::string help_title;
	};

	int n = 0;
	std::vector<dir> dir_list;
	std::vector<std::string> current_input;

	void InsertDir(std::string dir_title, std::string parent_title = "");
	void Insert(std::string dir_title, commands com_list);
	void Insert(std::string title, std::function<void()>func, int argsize, std::string help_title = "");
	void Input();

private:
	void tokenizer(std::string s, std::vector<std::string>* v);
};

#endif // !__CLI


