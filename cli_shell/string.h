#pragma once
#ifndef __STRING
#define __STRING
#include <string>
namespace color
{
	struct rgb
	{
		int r;
		int g;
		int b;
	};
	enum COL
	{
		TEXT = 0,
		OUT,
		ERROR,
		SUCCESS,
		INFO
	};
	void print_color(int COL, std::string data);
	void print_color(rgb color, std::string data);
}

namespace string
{
	std::string trim(const std::string& str,
		const std::string& whitespace = " \t");

	std::string reduce(const std::string& str,
		const std::string& fill = " ",
		const std::string& whitespace = " \t");
}

#endif __STRING
