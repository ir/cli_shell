#include "string.h"

void color::print_color(int COL, std::string data)
{
    rgb color = { 255,255,255 };
    switch (COL)
    {
    case TEXT: color = { 255,0,255 };
          break;
    case OUT: color = { 200,235,255 };
          break;
    case ERROR: color = { 255,0,0 };
          break;
    case SUCCESS: color = { 0,255,0 };
          break;
    case INFO: color = { 95,95,225 };
          break;
    default: color = { 255,255,255 };
           break;
    }
    printf("\033[38;2;%d;%d;%dm%s\033[0m", color.r, color.g, color.b, data.c_str());
}

void color::print_color(rgb color, std::string data)
{
    printf("\033[38;2;%d;%d;%dm%s\033[0m", color.r, color.g, color.b, data.c_str());
}

std::string string::trim(const std::string& str, const std::string& whitespace)
{
    const auto strBegin = str.find_first_not_of(whitespace);
    if (strBegin == std::string::npos)
        return ""; // no content

    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}

std::string string::reduce(const std::string& str, const std::string& fill, const std::string& whitespace)
{
    // trim first
    auto result = trim(str, whitespace);

    // replace sub ranges
    auto beginSpace = result.find_first_of(whitespace);
    while (beginSpace != std::string::npos)
    {
        const auto endSpace = result.find_first_not_of(whitespace, beginSpace);
        const auto range = endSpace - beginSpace;

        result.replace(beginSpace, range, fill);

        const auto newStart = beginSpace + fill.length();
        beginSpace = result.find_first_of(whitespace, newStart);
    }

    return result;
}
