#include "CLI.h"
#include "string.h"

CLI::CLI()
{
	color::print_color(color::INFO, "CLI created\n");
}

CLI::~CLI()
{
	color::print_color(color::SUCCESS, "CLI destroyed\n");
}

void CLI::Insert(std::string title, std::function<void()>func, int argsize, std::string help_title)
{
	if (title.length() == 0)
		return;
	else if (title.length() > 16)
		title = title.substr(0, 16);
	bool is_menu = false;
	if (title.at(0) == '_')
	{
		is_menu = true;
		title = title.substr(1, title.length());
	}
		
	//clean up
	title = string::reduce(title);
	title = string::trim(title);
	std::transform(title.begin(), title.end(), title.begin(), ::tolower);
	
	//first char uppercase
	std::string h_t = title;
	while (h_t.length() < 16)
		h_t += " ";
	if (!std::isupper(h_t.at(0)))
		h_t.at(0) = std::toupper(h_t.at(0));
	
	if (is_menu)
		dir_list.push_back({h_t,title});
	
	command_list.push_back({ title,help_title,h_t,func,argsize });
}

void CLI::Input()
{
	color::print_color({ 159,94,224 }, CLI::cur_dir);
	color::print_color({ 94,159,224 }, " > ");
	//get user input
	std::string input = "";
	std::getline(std::cin, input);

	if (input.length() == 0)
		return;
	for (const char c : input)
	{
		if (!std::isalnum(c) && c != ' ')
		{
			color::print_color(color::ERROR, "only characters and integers are allowed\n");
			return;
		}
	}

	//clean up
	input = string::reduce(input);
	input = string::trim(input);
	std::transform(input.begin(), input.end(), input.begin(), ::tolower);
	//store input sep by spaces into current_input vec
	tokenizer(input, &current_input); 
	
	//iterate commands
	for (const auto& c : command_list)
	{
		if (current_input.size() > std::get<4>(c) + 1)
		{
			color::print_color(color::ERROR, "Too many arguments\n\n");
			return;
		}
		//input equal to title
		if (current_input.at(0) == std::get<0>(c))
		{
			//function call
			if (!std::get<3>(c) == NULL)
				std::get<3>(c)();
			std::cout << "\n";
			return;
		}
	}
	color::print_color(color::ERROR, "Invalid command\n\n");
	return;
}

void CLI::tokenizer(std::string s, std::vector<std::string>* v)
{
	if (v->size() != 0)
		v->clear();
	size_t argc = std::count(s.begin(), s.end(), ' ');
	std::stringstream ss(s);
	std::string word;
	while (ss >> word) {
		v->push_back(word);
	}
}
