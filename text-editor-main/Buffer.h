#include "global.h"
class Buffer
{
public:
    Buffer();
    vector<string> textLines;
    void insert(string, int);
    void append(string);
    void remove(int);
    string replaceTabsWithSpaces(string);
};