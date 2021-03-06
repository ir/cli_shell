#include "CLI.h"
#include "string.h"
#include "fcmds.h"
#include <thread>
CLI::CLI()
{	
	SetConsoleTitleA((LPCSTR)"console");
	color::print_color(color::C_INFO, "CLI created\n");
}

CLI::~CLI()
{
	color::print_color(color::C_SUCCESS, "CLI destroyed\n");
}

void CLI::InsertDir(std::string title, std::string parent)
{
	if (parent == "__BASE_MENU") // adding the base parent menu
	{
		for (const auto& d : dir_list)
		{
			if (d.parent == "__BASE_MENU")
				return;
		}
		
		dir_list.push_back({ title,parent,{{ "help",FCMDS::Help,0,"Help Title" } }});
		cur_dir = title;
	}
	else // submenu
	{
		dir_list.push_back({ title,parent,{{ "help",FCMDS::Help,0,"Help title"}}});

		for (auto& d : dir_list) 
		{
			if (d.title == parent)
			{
				d.com_list.push_back({title,NULL,0,"_Submenu of: " + d.title});
				color::print_color(color::C_OUT, "[+] added submenu:    " + d.title + " of: " + d.parent + "\n");
			}
			else if (d.title == title)
			{
				d.com_list.push_back({ parent,NULL,0,"_ParentMenu of: " + d.title });
				color::print_color(color::C_OUT, "[+] added parentmenu: " + d.parent + " of: " + d.title + "\n");
			}
		}
	}
}

void CLI::Insert(std::string dir_title, commands com_list)
{
	if (com_list.title.length() == 0)
		return;
	else if (com_list.title.length() > 16)
		com_list.title = com_list.title.substr(0, 16);

	bool found = false;
	size_t i = 0;
	while (found == false && i < dir_list.size()) // finding parent dir
	{
		if (dir_list.at(i).title == dir_title)
		{
			//color::print_color(color::C_OUT, "[+] found " + dir_title + "\n");
			found = true;
			break;
		}
		else
		{
			i++;
			continue;
		}
	}
	
	//clean up, tolower
	com_list.title = string::reduce(com_list.title.c_str());
	com_list.title = string::trim(com_list.title.c_str());
	std::transform(com_list.title.begin(), com_list.title.end(), com_list.title.begin(), ::tolower);
	
	for (auto& d : dir_list) // inserting dir
	{
		if (d.title == dir_title)
		{
			color::print_color(color::C_SUCCESS, "[+] added " + com_list.title + " to " + d.title + "\n");
			d.com_list.push_back(com_list);
		}
	}
}

void CLI::Input()
{
	color::print_color({ 224,94,159 }, cur_dir);
	color::print_color({ 94,159,224 }, "\nB> ");
	//user input
	std::string input = "";
	std::getline(std::cin, input);
	if (input.length() == 0)
		return;

	//clean up
	input = string::reduce(input);
	input = string::trim(input);
	//converting first command to lower
	std::transform(input.begin(), input.begin() + 1, input.begin(), ::tolower);
	//store input sep by spaces into current_input vec
	tokenizer(input, &current_input); 
	size_t input_size = current_input.size() - 1;
	//iterate commands
	for (const auto& d : dir_list)
	{
		//getting correct dir
		if (d.title == cur_dir)
		{
			for (size_t i = 0; i < d.com_list.size(); i++)
			{
				//argsize check
				if (input_size > (size_t)d.com_list.at(i).argsize && d.com_list.at(i).title == current_input.at(0))
				{
					color::print_color(color::C_ERROR, "Too many arguments\n\n");
					return;
				}
				else if (input_size < 1 && d.com_list.at(i).argsize > 0 && d.com_list.at(i).title == current_input.at(0))
				{
					color::print_color(color::C_ERROR, "Not enough arguments\n\n");
					return;
				}

				std::vector<std::optional<std::string>> a{};
				std::string st;
				std::optional<std::string> s;
				bool is_thread = false;
				//storing arguments into one string instead of vector (? dont remember what this comment was for)
				if (input_size > 0) // checks for arguments, then checks if its a thread (1st arg). (dont remember why i was doing this but its here, not sure if the code for running functions even supports threads)
				{
					for (size_t j = 1; j < current_input.size(); j++)
						a.push_back(current_input.at(j));
					if (a[0] == "-t")
					{
						is_thread = true;
						a.erase(a.begin());
						if (a.size() < 1)
						{
							color::print_color(color::C_ERROR, "Not enough arguments\n\n");
							return;
						}
					}
					
					for (auto& d : a)
						if (d.has_value())
							st += d.value() + ' ';
					st.resize(st.size() - 1);
					s = st;
					
				}
				//accessing correct command struct to call func
				if (current_input.at(0) == d.com_list.at(i).title)
				{
					if (d.com_list.at(i).func != NULL)
					{
						if (is_thread)
						{
							color::print_color(color::C_OUT, "[+] thread\n");
							std::thread t(d.com_list.at(i).func, s);
							t.join(); // as stated previously, probably doesnt even work
						}
						else
							d.com_list.at(i).func(s);
						
						return;
					}
				}
				else // changing dir (this is a weird hack but it works so oh well)
				{
					for (auto& dd : dir_list)
					{
						if ((current_input.at(0) == dd.parent && dd.parent != "__BASE_MENU"))
						{
							FCMDS::ChangeDir(cur_dir, dd.parent);
							return;
						}
						else if ((current_input.at(0) == dd.title && dd.parent == d.title) && dd.title != d.title)
						{
							FCMDS::ChangeDir(cur_dir, current_input.at(0));
							return;
						}
					}
				}
			}	
		}
	}
	color::print_color(color::C_ERROR, "Invalid command\n\n");
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
