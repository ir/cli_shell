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

void CLI::InsertDir(std::string title, std::string parent)
{
	
	if (parent == "__BASE_MENU")
	{
		dir_list.push_back({ title,parent,{} });
		cur_dir = title;
	}
	else 
	{
		sub_titles.push_back(title);
		
		//add submenu to vector
		dir_list.push_back({ title,parent,{} });
		for (auto& d : dir_list)
		{
			if (d.title == parent)
			{
				for (auto& s : sub_titles)
				{
					if (title == s)
						st = s;
				}
				d.com_list.push_back({ title,[&]() {FCMDS::ChangeDir(cur_dir,st); },0,"Submenu" });
			}
		}
		//add submenu to parent menu as item
	}
}

void CLI::Insert(std::string dir_title, commands com_list)
{
	if (com_list.title.length() == 0)
		return;
	else if (com_list.title.length() > 16)
		com_list.title = com_list.title.substr(0, 16);
	//clean up, tolower
	com_list.title = string::reduce(com_list.title.c_str());
	com_list.title = string::trim(com_list.title.c_str());
	std::transform(com_list.title.begin(), com_list.title.end(), com_list.title.begin(), ::tolower);
	
	for (auto& d : dir_list)
	{
		//std::cout << d.title << std::endl;
		//std::cout << dir_title << std::endl;
		if (d.title == dir_title)
		{
			color::print_color(color::SUCCESS, "[+] added: " + com_list.title + " to: " + d.title + "\n");
			d.com_list.push_back(com_list);
		}
	}
}

void CLI::Input()
{
	color::print_color({ 94,94,224 }, cur_dir);
	color::print_color({ 94,159,224 }, " > ");
	//user input
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
		if (d.title == cur_dir)
		{
			for (int i = 0; i < d.com_list.size(); i++)
			{
				//argsize check
				if (current_input.size() > d.com_list.at(i).argsize + 1)
				{
					color::print_color(color::ERROR, "Too many arguments\n");
					return;
				}
				
				//accessing correct command struct
				if (current_input.at(0) == d.com_list.at(i).title)
				{
					if (d.com_list.at(i).func != NULL)
					{
						d.com_list.at(i).func();
						return;
					}
				}
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
