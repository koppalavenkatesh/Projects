#include "Buffer.h"
class Editor
{
public:
    int x, y;
    char mode;
    Buffer *buff;
    string status, fileName;
    string tos(int);
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void deleteLine();
    void deleteLine(int);
    void saveFile();
    Editor();
    Editor(string);
    char getMode() { return mode; }
    void handleInput(int);
    void printBuff();
    void printStatusLine();
    void updateStatus();
};