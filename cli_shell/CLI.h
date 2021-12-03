#pragma once
#ifndef __CLI
#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include <sstream>
#include <map>
#include <algorithm>
#include <functional>
#include "string.h"
#endif // !__CLI

namespace hi
{
	void functhing()
	{
		std::cout << "func call\n";
	}
}

class CLI
{
public:
	CLI();
	~CLI();

	void Insert(std::string title,std::function<void()>func, std::string help_title = "")
	{
		if (title.length() == 0)
			return;
		else if (title.length() > 16)
			title = title.substr(0, 16);
		//clean up
		title = string::reduce(title);
		title = string::trim(title);
		std::transform(title.begin(), title.end(), title.begin(), ::tolower);
		//com_func_map.insert({ item_count,func });
		command_list.push_back({ title,help_title,item_count,func });
		item_count++;
	}

	void Input()
	{
		std::cout << " > ";
		//get user input
		std::string input = "";
		std::getline(std::cin, input);
		if (input.length() == 0)
			return;
		//clean up
		input = string::reduce(input);
		input = string::trim(input);
		std::transform(input.begin(), input.end(), input.begin(), ::tolower);
		//store input sep by spaces into current_input vec
		tokenizer(input, &current_input);
		//iterate commands
		for (const auto& c : command_list)
		{
			//input equal to title
			if (input == std::get<0>(c))
			{
				//call function corresponding to item_count
				std::get<3>(c)();
				std::cout << "\n";
				return;
			}
		}
		std::cout << "Invalid command\n";
		return;
	}

private:
	int item_count = 0;
	std::map<int,std::function<void()>> com_func_map = {};
	std::vector<std::tuple<std::string, std::string, int,std::function<void()>>> command_list = {};
	std::vector<std::string> current_input;

	void tokenizer(std::string s, std::vector<std::string>* v)
	{
		if (v->size() != 0)
			v->clear();
		size_t argc = std::count(s.begin(), s.end(), ' ');
		std::stringstream ss(s);
		std::string word;
		while (ss >> word) {
			v->push_back(word);
		}
	}

};

CLI::CLI()
{
	std::cout << "CLI created\n";
}

CLI::~CLI()
{
	std::cout << "CLI destroyed\n";
}

