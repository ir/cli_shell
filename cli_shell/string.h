#pragma once
#ifndef __STRING
#include <string>
#endif // !__STRING

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

    void print_color(int COL, std::string data)
    {
        rgb color = {255,255,255};
        switch (COL)
        {
        case 0: color = { 255,0,255 };
            break;
        case 1: color = { 200,235,255 };
            break;
        case 2: color = { 255,0,0 };
            break;
        case 3: color = { 0,255,0 };
            break;
        case 4: color = { 95,95,225 };
            break;
        default: color = { 255,255,255 };
            break;
        }
        printf("\033[38;2;%d;%d;%dm%s\033[0m", color.r,color.g,color.b,data.c_str());
    }

    void print_color(rgb color, std::string data)
    {
        printf("\033[38;2;%d;%d;%dm%s\033[0m", color.r, color.g, color.b, data.c_str());
    }
}

namespace string
{
    std::string trim(const std::string& str,
        const std::string& whitespace = " \t")
    {
        const auto strBegin = str.find_first_not_of(whitespace);
        if (strBegin == std::string::npos)
            return ""; // no content

        const auto strEnd = str.find_last_not_of(whitespace);
        const auto strRange = strEnd - strBegin + 1;

        return str.substr(strBegin, strRange);
    }

    std::string reduce(const std::string& str,
        const std::string& fill = " ",
        const std::string& whitespace = " \t")
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
}