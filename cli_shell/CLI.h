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

	struct Dir
	{
		std::string title;
		std::string parent;
		std::vector<commands> com_list;
	};
	
	std::string st;
	std::vector<std::string> sub_titles;
	std::string cur_dir = "";
	std::vector<Dir> dir_list;
	//0 = cur command, others = args
	std::vector<std::string> current_input;
	//create new dir
	void InsertDir(std::string title, std::string parent = "");
	//insert item into dir
	void Insert(std::string dir_title, commands com_list);
	//user input
	void Input();

private:
	void tokenizer(std::string s, std::vector<std::string>* v);
};

#endif // !__CLI


