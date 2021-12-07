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
	
	
	//insert dir 
	cli.InsertDir("home", "__BASE_MENU");
	cli.InsertDir("sub", "home");
	cli.InsertDir("ssub", "sub");
	cli.InsertDir("asub", "home");
	
	//insert dir items
	cli.Insert("home", { "print",FCMDS::Printer,16,"Prints a string" });
	cli.Insert("home", { "title",FCMDS::ChangeTitle,16,"Changes the console's title" });
	

	//cli.Insert("sub", { "cls",{FCMDS::Cls},0,"Clears the screen" });
	
	while (1)
	{
		cli.Input();
	}
}
