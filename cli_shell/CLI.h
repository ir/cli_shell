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


	struct commands
	{
		std::string title;
		std::function<void()> func;
		int argsize;
		std::string help_title;
	};

	struct _Dir
	{
		std::string title;
		std::string parent;
		std::vector<commands> com_list;
	};
	
	
	std::string cur_dir = "home";
	std::vector<_Dir> _dir_list;
	
	std::vector<std::string> current_input;

	void InsertDir(std::string title, std::string parent_title = "");
	void Insert(std::string dir_title, commands com_list);
	void Input();

private:
	void tokenizer(std::string s, std::vector<std::string>* v);
};

#endif // !__CLI


