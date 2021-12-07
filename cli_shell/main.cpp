// CLI_shell.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "CLI.h"
#include "fcmds.h"
extern CLI cli;

void call(std::string str)
{
	std::cout << str << std::endl;
}

int main()
{
	
	
	// insert dir 
	cli.InsertDir("home", "__BASE_MENU");
	cli.InsertDir("sub", "home");
	cli.InsertDir("ssub", "sub");
	cli.InsertDir("asub", "home");
	
	
	
	//cli.Insert("home", { "cls",{FCMDS::Cls }, 0, "clears the screen"});
	cli.Insert("home", { "print",{FCMDS::Printer},2,"prints" });
	// insert dir items
	
	
	while (1)
	{
		cli.Input();
	}
}
