#include "fcmds.h"
#include "CLI.h"
#include <Windows.h>
CLI cli;


void FCMDS::ChangeDir(std::string cur_dir, std::string new_dir)
{
	cli.cur_dir = new_dir;
	color::print_color(color::C_OUT, "[+] new dir: " + cli.cur_dir + "\n");
	
}

void FCMDS::ChangeTitle(std::vector<std::optional<std::string>> str)
{
	std::string s;
	for (auto& d : str)
		if (d.has_value())
			s += d.value() + " ";
	s.resize(s.size() - 1);

	if(SetConsoleTitleA((LPCSTR)s.c_str()))
		color::print_color(color::C_OUT, "set the title to: " + s + "\n");
}

void FCMDS::Printer(std::vector<std::optional<std::string>> str)
{
	std::string s;
	for (auto& d : str)
		if (d.has_value())
			s += d.value() + " ";
	s.resize(s.size() - 1);
	
	color::print_color(color::C_INFO,s + "\n");
}

void FCMDS::Cls(std::vector<std::optional<std::string>> str)
{
	system("cls");
}

void FCMDS::Help(std::vector<std::optional<std::string>> str)
{
	color::print_color({ 94,224,224 }, "list of all commands:\n");
	
	for (const auto& d : cli.dir_list)
	{
		if (d.title == cli.cur_dir)
		{
			for (int i = 0; i < d.com_list.size(); i++)
			{
				std::string title = d.com_list.at(i).title;
				if (title.length() > 16)
					title = title.substr(0, 16);

				while (title.length() < 16)
					title += " ";
				if (!std::isupper(title.at(0)))
					title.at(0) = std::toupper(title.at(0));

				color::print_color(color::C_TEXT, " " + title
					+ d.com_list.at(i).help_title);
				printf("\n");
			}
		}
	}
	printf("\n");
}


