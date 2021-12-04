#include "fcmds.h"
#include "CLI.h"
CLI cli;

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
}