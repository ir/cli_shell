#include "fcmds.h"
#include "CLI.h"
CLI cli;

void FCMDS::ChangeDir(std::string cur_dir, std::string new_dir)
{
	cli.cur_dir = new_dir;
	color::print_color(color::C_OUT, "[+] new dir: " + cli.cur_dir + "\n");
	
}

void FCMDS::ChangeTitle(std::optional<std::string> str)
{
	std::string s = str.value();

	if (SetConsoleTitleA((LPCSTR)s.c_str()))
	{
		color::print_color(color::C_OUT, "set the title to: " + s + "\n\n");
	}
}

void FCMDS::Printer(std::optional<std::string> str)
{
	std::string s = str.value();
	
	color::print_color(color::C_OUT,s + "\n\n");
}

void FCMDS::sysc(std::optional<std::string> str)
{
	system(str.value().c_str());
	system("cls");
}

void FCMDS::Cls(std::optional<std::string> str)
{
	system("cls");
}

void HELPER::get_out(const char* cmd, std::string& buffer_array)
{
	std::array<char, 1024> buffer;
	std::string result;
	std::unique_ptr<FILE, decltype(&_pclose)> pipe(_popen(cmd, "r"), _pclose);
	if (!pipe) {
		throw std::runtime_error("_popen() failed!");
	}
	while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
		result += buffer.data();
	}
	buffer_array = result;
}

void FCMDS::roblox::unlock_fps(std::optional<std::string> str)
{
	FCMDS::sysc("D:\\projects\\rbxfpsunlocker.exe");
}

void FCMDS::read_exec(std::optional<std::string> str)
{
	std::string buffer;
	char cur;
	std::vector<std::string> v;
	cli.tokenizer(str.value(), &v);
	
	
	HELPER::get_out(str.value().c_str(), buffer);
	color::print_color(color::C_OUT, buffer + "\n");
}

void FCMDS::roblox::multi_client(std::optional<std::string> str)
{
	if (CreateMutex(NULL, TRUE, L"ROBLOX_singletonMutex")) //bInitialOwner is TRUE, takes ownership and holds it until this process exits
		color::print_color(color::C_SUCCESS, "[+] now able to use multiple clients\n\n");
}

void FCMDS::AttachCon(std::optional<std::string> str)
{
	LPWSTR pName = (LPWSTR)str.value().c_str();
	HWND hWnd = FindWindowA(0, (LPCSTR)pName);
	if (!hWnd)
	{
		color::print_color(color::C_ERROR, "[-] couldnt find window, error " + std::to_string(GetLastError()));
		return;
	}

	DWORD pId;
	GetWindowThreadProcessId(hWnd, &pId);

	color::print_color(color::C_SUCCESS, "[+] found window " + str.value() + "\n");
	color::print_color(color::C_SUCCESS, "[+] found processid " + std::to_string(pId) + "\n");

	FreeConsole();
	
	AttachConsole(pId);
	
	if (AllocConsole())
	{
		color::print_color(color::C_SUCCESS, "[+] attached to process " + str.value() +
			+" with processid " + std::to_string(pId) + "\n");
		SetConsoleTitleA((LPCSTR)pName);
	}
}

void FCMDS::Help(std::optional<std::string> str)
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

				color::print_color(color::C_TEXT, " " + title
					+ d.com_list.at(i).help_title);
				printf("\n");
			}
		}
	}
	printf("\n");
}