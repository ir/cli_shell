#pragma once
#ifndef __FCMDS
#define __FCMDS
#include <iostream>
#include <optional>
#include <vector>
#include <Windows.h>
#include <array>
#include "string.h"

namespace HELPER
{
	void get_out(const char* cmd, std::string& buffer_array);
}

namespace FCMDS
{
	void ChangeDir(std::string cur_dir, std::string new_dir);

	//make error handler
	//call color_print then pass getlasterror converted as string?
	void Help(std::optional<std::string> str);
	void read_exec(std::optional<std::string> str);
	void Printer(std::optional<std::string> str);
	void ChangeTitle(std::optional<std::string> str);
	void Cls(std::optional<std::string> str);
	void AttachCon(std::optional<std::string> str);
}
#endif // !__FCMDS
