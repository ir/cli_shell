#include "fcmds.h"
#include "CLI.h"
CLI cli;

void FCMDS::ChangeDir(std::string cur_dir, std::string new_dir)
{
	cli.cur_dir = new_dir;
	
}

void FCMDS::Printer()
{
	color::print_color(color::INFO, "test\n");
}

void FCMDS::Help()
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

				color::print_color(color::TEXT, " " + title
					+ d.com_list.at(i).help_title);
				printf("\n");
			}
		}
	}
}

