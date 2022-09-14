#include "global.h"
#include "Editor.h"
using namespace std;
void initialize()
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, true);
    // scrollok(stdscr, true);
}

int main(int argc, char *argv[])
{
    string fileName = "";
    Editor ed;
    if (argc > 1)
    {
        fileName = argv[1];
        ed = Editor(fileName);
    }
    else
        ed = Editor();

    initialize();
    while (ed.getMode() != 'x')
    {
        ed.updateStatus();
        ed.printStatusLine();
        ed.printBuff();
        int ch = getch();
        if(ed.mode=='n' && ch=='s')
        {
            ed.saveFile();
            ed.status="File saved";
            continue;
        }
        if(ed.mode=='n' && ch=='x')
            break;
        if(ed.mode=='n' && ch!='i')
            continue;
        
        ed.handleInput(ch);
    }
    refresh();
    endwin();
}