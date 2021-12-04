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
class CLI
{
public:
	CLI();
	~CLI();

	std::string cur_dir = "home";
	int n = 0;
	std::vector <std::vector<std::string>> dir_list = { {cur_dir, "_home" }
};
	std::vector<std::tuple<std::string, std::string, std::string, std::function<void()>,int>> command_list{};
	std::vector<std::string> current_input;

	void Insert(std::string title, std::function<void()>func, int argsize, std::string help_title = "");
	void Input();

private:
	void tokenizer(std::string s, std::vector<std::string>* v);
};

#endif // !__CLI


