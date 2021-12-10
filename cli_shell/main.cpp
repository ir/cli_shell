// CLI_shell.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <array>
#include "CLI.h"
#include "fcmds.h"

extern CLI cli;


int main()
{
	
	//insert dir 
	cli.InsertDir("home", "__BASE_MENU");
	cli.InsertDir("roblox", "home");
	cli.InsertDir("con", "home");

	//insert dir items
	cli.Insert("home",{ "print", FCMDS::Printer,    16,"Prints a string" });
	//roblox
	cli.Insert("roblox", { "multi",FCMDS::roblox::multi_client,0,"Allows you to open multiple clients" });
	//cli.Insert("roblox", { "unlockfps",FCMDS::roblox::unlock_fps,0,"Allows you to unlock your fps" });
	//con
	cli.Insert("con", { "title", FCMDS::ChangeTitle,16,"Changes the console's title" });
	cli.Insert("con", { "cls",   FCMDS::Cls,        0, "Clears the console screen" });
	cli.Insert("con", { "attach",FCMDS::AttachCon,  8, "Attaches the console to a process" });
	cli.Insert("con", { "exec",  FCMDS::read_exec,  8, "Prints output from executed command" });
	cli.Insert("con", { "call",  FCMDS::sysc,       8, "Executes a system call" });

	while (1)
	{
		cli.Input();
	}
}
