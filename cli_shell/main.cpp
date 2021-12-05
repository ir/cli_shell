// CLI__shell.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "CLI.h"
#include "fcmds.h"
extern CLI cli;

int main()
{
	cli.InsertDir("", "home");
	cli.Insert("home", { "Help",FCMDS::Help,0,"Lists all available commands" });
	cli.Insert("home", { "Print",FCMDS::Printer,0,"This is the print title" });
	cli.InsertDir("home", "submenu");
	cli.Insert("submenu", { "Printer",FCMDS::ChangeDir,0,"This is the printer title" });
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
