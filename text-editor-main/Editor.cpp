#include "global.h"
#include "Editor.h"

Editor::Editor()
{
    x = 0;
    y = 0;
    mode = 'n';
    status = "Normal mode";
    fileName = "untitled";
    buff = new Buffer();
    buff->append("");
}

Editor::Editor(string fileNameInp)
{
    x = 0;
    y = 0;
    mode = 'n';
    status = "Normal mode";
    fileName = fileNameInp;
    buff = new Buffer();
    ifstream infile(fileName.c_str());
    if (infile.is_open())
    {
        while (!infile.eof())
        {
            string temp;
            getline(infile, temp);
            buff->append(temp);
        }
    }
    else
    {
        cerr << "Cannot open file: '" << fileName << "'\n";
        buff->append("");
    }
}

void Editor::updateStatus()
{
    switch (mode)
    {
    case 'n':
        status = "Normal Mode";
        break;
    case 'i':
        status = "Insert Mode";
        break;
    case 'x':
        status = "Exiting";
        break;
    }
    status += "\tCOL: " + to_string(x) + "\tROW: " + to_string(y);
}

void Editor::handleInput(int c)
{
    switch (c)
    {
    case KEY_LEFT:
        moveLeft();
        return;
    case KEY_RIGHT:
        moveRight();
        return;
    case KEY_DOWN:
        moveDown();
        return;
    case KEY_UP:
        moveUp();
        return;
    default:
        break;
    }
    switch (mode)
    {
    case 'n':
        switch (c)
        {
        case 's':
            saveFile();
            break;
        case 'i':
            mode = 'i';
            break;
        case 'x':
            mode = 'x';
            break;
        default:
            break;
        }

    case 'i':
        switch (c)
        {
        case 27: //escape
            mode = 'n';
            break;
        case KEY_BACKSPACE:
            if (x == 0 && y > 0)
            {
                x = buff->textLines[y - 1].length();
                buff->textLines[y - 1] += buff->textLines[y];
                deleteLine();
                moveUp();
            }
            else if (x == 0 && y == 0)
            {
            }
            else
            {
                x--;
                buff->textLines[y].erase(x, 1);
            }
            break;
        case 10:
        case KEY_ENTER:
            if (x < buff->textLines[y].length())
            {
                buff->insert(buff->textLines[y].substr(x, buff->textLines[y].length() - x), y + 1);
                buff->textLines[y].erase(x, string::npos);
            }
            else
            {
                buff->insert("", y + 1);
                x = 0;
            }
            moveDown();
            break;
        case 9: //tab
            buff->textLines[y].insert(x, 4, ' ');
            x += 4;
            break;
        default:
            buff->textLines[y].insert(x++, 1, char(c));
            break;
        }
        break;
    }
}

void Editor::moveUp()
{
    if (y == 0)
        return;
    y--;
    if (x > buff->textLines[y].length())
        x = buff->textLines[y].length();
    move(y, x);
}
void Editor::moveDown()
{
    if (y + 1 < buff->textLines.size())
    {
        y++;
    }
    if (x > buff->textLines[y - 1].length())
        x = buff->textLines[y].length();
    move(y, x);
}

void Editor::moveLeft()
{
    if (x > 0)
        x--;
    else
    {
        y--;
        x = buff->textLines[y].length();
    }
    move(y, x);
}

void Editor::moveRight()
{
    if (x + 1 < COLS && x + 1 <= buff->textLines[y].length())
    {
        x++;
        move(y, x);
    }
}

void Editor::printBuff()
{
    for (int i = 0; i < LINES - 1; i++)
    {
        if (i >= buff->textLines.size())
        {
            move(i, 0);
            clrtoeol();
        }
        else
        {
            mvprintw(i, 0, buff->textLines[i].c_str());
        }
        clrtoeol();
    }
    move(y, x);
}

void Editor::printStatusLine()
{
    attron(A_REVERSE);
    mvprintw(LINES - 1, 0, status.c_str());
    clrtoeol();
    attroff(A_REVERSE);
}

void Editor::deleteLine()
{
    buff->remove(y);
}

void Editor::deleteLine(int i)
{
    buff->remove(i);
}

void Editor::saveFile()
{
    if (fileName == "")
    {
        // Set filename to untitled
        fileName = "untitled";
    }

    ofstream f(fileName.c_str());
    if (f.is_open())
    {
        for (int i = 0; i < buff->textLines.size(); i++)
        {
            f << buff->textLines[i] << endl;
        }
        status = "Saved to file!";
    }
    else
    {
        status = "Error: Cannot open file for writing!";
    }
    f.close();
}
