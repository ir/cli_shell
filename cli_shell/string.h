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
		C_TEXT = 0,
		C_OUT,
		C_ERROR,
		C_SUCCESS,
		C_INFO
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
