#include "CLI.h"
#include "string.h"
#include "fcmds.h"
CLI::CLI()
{
	color::print_color(color::INFO, "CLI created\n");
}

CLI::~CLI()
{
	color::print_color(color::SUCCESS, "CLI destroyed\n");
	
}

void CLI::InsertDir(std::string dir_title, std::string parent_title)
{
	dir_list.push_back({ dir_title,parent_title,{} });
	for (auto& d : dir_list)
	{
		if (parent_title == d.dir_title && d.parent_title.length() != 0)
		{
			d.com_list.push_back({ parent_title,[&] {FCMDS::ChangeDir(cur_dir, d.dir_title); },0,"__Submenu of " + parent_title });
		}
		if (dir_title == d.parent_title && d.parent_title.length() != 0)
		{
			d.com_list.push_back({ dir_title,[&] {FCMDS::ChangeDir(cur_dir,d.parent_title); },0,"__Parentmenu of " + dir_title });

		}
	}
}

void CLI::Insert(std::string dir_title, commands com_list)
{
	if (com_list.title.length() == 0)
		return;
	else if (com_list.title.length() > 16)
		com_list.title = com_list.title.substr(0, 16);

	//clean up
	com_list.title = string::reduce(com_list.title);
	com_list.title = string::trim(com_list.title);
	std::transform(com_list.title.begin(), com_list.title.end(), com_list.title.begin(), ::tolower);

	for (auto& d : dir_list)
	{
		if (dir_title == d.dir_title)
		{
			color::print_color(color::SUCCESS, "good\n");
			d.com_list.push_back({ com_list.title,com_list.func,com_list.argsize, com_list.help_title });
		}
	}
}

void CLI::Input()
{
	color::print_color({ 94,94,224 }, cur_dir);
	color::print_color({ 94,159,224 }, " > ");
	//get user input
	std::string input = "";
	std::getline(std::cin, input);

	if (input.length() == 0)
		return;
	for (const char c : input)
	{
		if (!std::isalnum(c) && c != ' ' && c != '_')
		{
			color::print_color(color::ERROR, "only characters and integers are allowed\n");
			return;
		}
	}

	//clean up
	input = string::reduce(input);
	input = string::trim(input);
	std::transform(input.begin(), input.end(), input.begin(), ::tolower);
	//store input sep by spaces into current_input vec
	tokenizer(input, &current_input); 
	
	//iterate commands
	for (const auto& d : dir_list)
	{
		for (int i = 0; i < d.com_list.size(); i++)
		{
			//argsize check
			if (current_input.size() > std::get<2>(d.com_list.at(i)) + 1) 
			{
				color::print_color(color::ERROR, "Too many arguments\n");
				return;
			}
			//check if input is equal to title
			if (current_input.at(0) == std::get<0>(d.com_list.at(i)))
			{
				if (!std::get<1>(d.com_list.at(i)) == NULL)
				{
					std::get<1>(d.com_list.at(i))();                                                                      
				}
					
				return;
			}
		}
	}
	
	color::print_color(color::ERROR, "Invalid command\n\n");
	return;
}

void CLI::tokenizer(std::string s, std::vector<std::string>* v)
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
