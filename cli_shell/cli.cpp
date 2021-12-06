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
	std::string* t = &title;
	if(parent == "")
		_dir_list.push_back({ title,parent,{} });
	else
	{
		_dir_list.push_back({ title,parent,{} });
		_Dir a;
		for (auto& c : _dir_list)
		{
			if (c.title == title)
				a = c;
		}

		for (auto& d : _dir_list)
		{
			if (parent == a.title)
			{
				d.com_list.push_back({ title,[&] {FCMDS::ChangeDir(cur_dir,*t); },0,"submenu_help" });
			}
		}
	}
}

/*
void CLI::InsertDir(std::string* title, std::string parent)
{
	if (parent == "")
		_dir_list.push_back({ *title,parent,{} });
	else
	{
		_dir_list.push_back({ *title,parent,{} });
		_Dir a;
		for (auto& c : _dir_list)
		{
			if (c.title == *title)
				a = c;
		}
		
		for (auto& d : _dir_list)
		{
			if (parent == d.title)
			{
				d.com_list.push_back({ title,[&] {FCMDS::ChangeDir(cur_dir,*title); },0,"submenu help" });
			}
		}
	}
}
*/
void CLI::Insert(std::string dir_title, commands command_list)
{
	std::string* c = &command_list.title;
	if (c->length() == 0)
		return;
	else if (c->length() > 16)
		*c = c->substr(0, 16);

	for (auto& c : _dir_list)
	{
		std::cout << c.title << std::endl;
		for (int i = 0; i < c.com_list.size(); i++)
		{
			std::cout << c.com_list.at(i).title << std::endl;
		}
	}

	//clean up
	*c = string::reduce(c->c_str());
	*c = string::trim(c->c_str());
	std::transform(c->begin(), c->end(), c->begin(), ::tolower);
	for (auto& d : _dir_list)
	{
		if (dir_title == d.title)
		{
			d.com_list.push_back(command_list);
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
	for (const auto& d : _dir_list)
	{
		
		if (d.title == cur_dir)
		{
			std::cout << "dir: " << d.title << std::endl;
			for (int i = 0; i < d.com_list.size(); i++)
			{
				std::cout << "item: " << d.com_list.at(i).title << std::endl;
				if (current_input.size() > d.com_list.at(i).argsize + 1)
				{
					color::print_color(color::ERROR, "Too many arguments\n");
					return;
				}
				//check if input is equal to title
				if (current_input.at(0) == d.com_list.at(i).title)
				{
					if (!d.com_list.at(i).func == NULL)
					{
						d.com_list.at(i).func();
					}

					return;
				}
			}
		}
	}
	for (const auto& d : _dir_list)
	{
		for (int i = 0; i < d.com_list.size(); i++)
		{
			//argsize check
			if (current_input.size() > d.com_list.at(i).argsize + 1)
			{
				color::print_color(color::ERROR, "Too many arguments\n");
				return;
			}
			
			//check if input is equal to title
			if (current_input.at(0) == d.com_list.at(i).title)
			{
				if (!d.com_list.at(i).func == NULL)
				{
					d.com_list.at(i).func();
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
