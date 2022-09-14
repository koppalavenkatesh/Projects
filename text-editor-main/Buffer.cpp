#include "global.h"
#include "Buffer.h"

Buffer::Buffer()
{
}

string Buffer::replaceTabsWithSpaces(string line)
{
    int tabPos = line.find("\t");
    while (tabPos != line.npos)
    {
        tabPos = line.find("\t");
        line.replace(tabPos, 1, "    ");
    }
    return line;
}

void Buffer::insert(string line, int n)
{
    line = replaceTabsWithSpaces(line);
    textLines.insert(textLines.begin() + n, line);
}

void Buffer::append(string line)
{
    line = replaceTabsWithSpaces(line);
    textLines.push_back(line);
}

void Buffer::remove(int n)
{
    textLines.erase(textLines.begin() + n);
}