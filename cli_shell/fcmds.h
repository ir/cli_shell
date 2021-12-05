#pragma once
#ifndef __FCMDS
#define __FCMDS
#include <iostream>
#include "string.h"
namespace FCMDS
{
	void ChangeDir(std::string cur_dir, std::string new_dir);
	void Help();
	void Printer();
}
#endif // !__FCMDS
