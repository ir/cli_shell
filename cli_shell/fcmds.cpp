#include "fcmds.h"
#include "CLI.h"
CLI cli;

void FCMDS::ChangeDir(std::string dir)
{
	
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
		for (int i = 0; i < d.com_list.size(); i++)
		{
			std::string title = std::get<0>(d.com_list.at(i));
			if (title.length() > 16)
				title = title.substr(0, 16);

			while (title.length() < 16)
				title += " ";
			if (!std::isupper(title.at(0)))
				title.at(0) = std::toupper(title.at(0));

			color::print_color(color::TEXT, " " + title
				+ std::get<3>(d.com_list.at(i)));
			printf("\n");
		}
		
	}

}

/*
void FCMDS::Help()
{
	color::print_color({ 94,224,224 }, "list of all commands:\n");
	
	for (const auto& m : cli.command_list)
	{
		color::print_color(color::TEXT, " " + std::get<2>(m) + " " + std::get<1>(m));
		for (const auto& d : cli.dir_list)
			for(const auto& s : d)
				if (s == std::get<0>(m))
					color::print_color(color::TEXT, " _SUBMENU_");
		printf("\n");
	}
}*/