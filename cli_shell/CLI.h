#pragma once
#ifndef __CLI
#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include <sstream>
#include "string.h"
#endif // !__CLI

class CLI
{
public:
	CLI();
	~CLI();

	void Insert(std::string title, std::string help_title = "")
	{
		if (title.length() == 0)
			return;
		title = string::reduce(title);
		title = string::trim(title);
		command_list.push_back({ title,help_title,item_count });
		item_count++;
		
		/*for (const auto& m : command_list)
		{
			std::cout<< std::get<2>(m);
		}*/
	}

	void Input()
	{
		//get user input
		std::string input = "";
		std::getline(std::cin, input);
		if (input.length() == 0)
			return;
		//clean up
		input = string::reduce(input);
		input = string::trim(input);
		//store input sep by spaces into current_input vec
		tokenizer(input, &current_input);
	}

private:
	int item_count = 0;
	std::vector<std::tuple<std::string,std::string,int>> command_list = {};
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

