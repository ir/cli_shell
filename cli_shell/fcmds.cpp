#include "fcmds.h"
#include "CLI.h"
CLI cli;

void FCMDS::Printer()
{
	std::cout << "printer\n";
}

void FCMDS::Help()
{
	color::print_color({ 255,215,220 }, "list of all commands:\n");
	for (const auto& m : cli.command_list)
	{
		color::print_color(color::TEXT, " " + std::get<0>(m) + "\n");
	}
}