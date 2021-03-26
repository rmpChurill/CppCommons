//------------------------------------------------------------------------------------------------------------
// Enthält allgemeine Hilfsfunktionen und -Klassen.
//------------------------------------------------------------------------------------------------------------

#pragma once

#include <string>
#include <sstream>
#include <vector>
#include <type_traits>
#include <ostream>
#include <algorithm>

#include "Config.hpp"

#undef min
#undef max

namespace
{
size_t PrepareFormat(const std::string &format, std::stringstream &buf, size_t pos)
{
    auto end = format.find('}', pos);

    return end == std::string::npos
               ? pos
               : end;
}

void FormatInternal(const std::string &format, std::stringstream &buf, size_t pos)
{
    while (pos < format.length() - 1)
    {
        if (format[pos] == '\\')
        {
            buf << format[pos + 1];
            pos += 2;
        }
        else
        {
            buf << format[pos];
            pos++;
        }
    }

    if (pos < format.length())
    {
        buf << format.back();
    }
}

template <typename TFirst, typename... TArgs>
void FormatInternal(const std::string &format, std::stringstream &buf, size_t pos, const TFirst &firstArg, const TArgs &... args)
{
    while (pos < format.length() - 1)
    {
        if (format[pos] == '%')
        {
            if (format[pos + 1] == '{')
                pos = PrepareFormat(format, buf, pos + 1);
            else
                buf << firstArg;

            FormatInternal(format, buf, pos + 1, args...);

            return;
        }
        else if (format[pos] == '\\')
        {
            buf << format[pos + 1];
            pos += 2;
        }
        else
        {
            buf << format[pos];
            pos++;
        }
    }

    if (pos < format.length())
    {
        if (format.back() == '%')
            buf << firstArg;
        else
            buf << format.back();
    }
}
} // namespace

namespace lib
{
template <typename T>
std::string ToString(const T &t)
{
    return (std::stringstream() << t).str();
}

template <typename TFirst, typename... TArgs>
std::string Format(const std::string &format, const TFirst &firstArg, const TArgs &... args)
{
    if (format.empty())
    {
        return std::string("");
    }

    std::stringstream buf;

    FormatInternal(format, buf, 0, firstArg, args...);

    return buf.str();
}

template <typename T>
const T &Clip(const T &value, const T &min, const T &max)
{
    return std::max(std::min(value, max), min);
}

template <typename T, typename TCompare = std::less<T>, typename TEquals = std::equal_to<T>>
void FilterUnique(std::vector<T> &vec, const TCompare &compare = TCompare(), const TEquals &equals = TEquals())
{
    std::sort(vec.begin(), vec.end(), compare);
    auto end = std::unique(vec.begin(), vec.end(), equals);
    vec.resize(end - vec.begin());
}
} // namespace lib