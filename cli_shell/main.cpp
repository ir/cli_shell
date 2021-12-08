// CLI_shell.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "CLI.h"
#include "fcmds.h"
#include <array>
extern CLI cli;


int main()
{
	//insert dir 
	cli.InsertDir("home", "__BASE_MENU");
	
	//insert dir items
	cli.Insert("home", { "print",FCMDS::Printer,    16,"Prints a string" });
	cli.Insert("home", { "title",FCMDS::ChangeTitle,16,"Changes the console's title" });
	cli.Insert("home", { "cls",  FCMDS::Cls,        0, "Clears the console screen" });
	cli.Insert("home", { "attach",FCMDS::AttachCon, 8, "Attaches the console to a process" });
	cli.Insert("home", { "exec", FCMDS::read_exec,   8, "Prints output from executed command" });

	while (1)
	{
		cli.Input();
	}
}
