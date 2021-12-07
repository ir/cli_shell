#pragma once
#ifndef __FCMDS
#define __FCMDS
#include <iostream>
#include "string.h"
#include <optional>
#include <vector>
namespace FCMDS
{
	void ChangeDir(std::string cur_dir, std::string new_dir);

	void Help(std::vector<std::optional<std::string>> str);
	void ChangeTitle(std::vector<std::optional<std::string>> str);
	void Printer(std::vector<std::optional<std::string>> str);
	void Cls(std::vector<std::optional<std::string>> str);
}
#endif // !__FCMDS
