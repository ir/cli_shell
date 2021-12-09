#pragma once
#ifndef __CCMDS
#define __CCMDS
#include <vector>

namespace console
{
	std::vector<int> get_size();
	void set_cursor_pos(short x, short y);
}

#endif // !__CCMDS

