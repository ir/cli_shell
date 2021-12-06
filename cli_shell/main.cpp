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
	// insert dir items
	cli.Insert("home", { "Help",FCMDS::Help,0,"Help help title"});
	//cli.Insert("home", { "Other",FCMDS::Printer,0,"other help title"});
	cli.InsertDir("sub", "home");
	cli.Insert("sub", {"Help", FCMDS::Help, 0, "Subhelp title"});
	cli.Insert("sub", { "print",FCMDS::Printer,0,"Print title" });
	cli.InsertDir("ssub", "sub");
	cli.Insert("ssub", { "Help",FCMDS::Help,0,"SSubhelp title" });
	while (1)
	{
		cli.Input();
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
