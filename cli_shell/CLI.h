#pragma once
#ifndef __CLI
#define __CLI
#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include<sstream>
#include <algorithm>
#include <functional>
class CLI
{
public:
	CLI();
	~CLI();

	int item_count = 0;
	std::vector<std::tuple<std::string, std::string, int, std::function<void()>>> command_list{};
	std::vector<std::string> current_input;

	void Insert(std::string title, std::function<void()>func, std::string help_title = "");
	void Input();

private:
	void tokenizer(std::string s, std::vector<std::string>* v);
};

#endif // !__CLI


