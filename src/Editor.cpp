#include "Editor.h"
#include <ncurses.h>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

Editor::Editor(string filename) :
  y(0),
  x(0),
  firstLine(0),
  mode('n'),
  fileName(filename),
  modeline("Welcome to editor!")
{
  curs_set(0);
  textWindow = newwin(getmaxy(stdscr)-2, getmaxx(stdscr), 0, 0);
  statusWindow = newwin(1, getmaxx(stdscr), getmaxy(stdscr)-2, 0);
  modeLineWindow = newwin(1, getmaxx(stdscr), getmaxy(stdscr)-1, 0);
  //y - 2 for modeline and statusline
  ifstream infile(filename.c_str());
  if(infile.is_open()) {
      while(!infile.eof()) {
	  string temp;
	  getline(infile, temp);
	  text.appendLine(temp+" \n");
      }
  }
  else {
    text.appendLine("");
  }
}

Editor::Editor()
{
  Editor("Unnamed");
}

void Editor::printText()
{
  int row(firstLine);
  const string *currentLine;
  wmove(textWindow,0,0);
  int printResult = 0;
  while (printResult == 0 && (currentLine = text.getLine(row))) {
    int collumn = 0;
    char currentCharacter;
    while (printResult == 0 && (currentCharacter = (*currentLine)[collumn])) {
      if (row == y && collumn == x) {
	wattron(textWindow, A_REVERSE);
      }
      printResult = wprintw(textWindow, string(1, currentCharacter).c_str());
      wattroff(textWindow, A_REVERSE);
      collumn++;
    }
    row++;
  }
}

void Editor::printStatus()
{
  wbkgd(statusWindow, A_REVERSE);
  status = "  LINE " + to_string(y) + "  COLL " + to_string(x) + "   <" + string(1,mode) + ">  ";
  mvwprintw(statusWindow, 0, 0, status.c_str());
  wrefresh(statusWindow);
}

void Editor::printModeline()
{
  wclear(modeLineWindow);
  mvwprintw(modeLineWindow, 0, 0, modeline.c_str());
  wrefresh(modeLineWindow);
  modeline.clear();
}

void Editor::moveUp()
{
  if (y - 1 >= 0) {
    y--;
    if(!text.inRange(y, x)) {
      x = text.getLine(y)->length()-2;
    }
  }
  else
    modeline = "Beginning of file";
}

void Editor::moveDown()
{
  if(text.inRange(y + 1)) {
    y++;
    if(!text.inRange(y, x)) {
      x = text.getLine(y)->length()-2;
    }
  }
  else
    modeline = "End of file";
}

void Editor::moveLeft()
{
  if (x - 1 >= 0) {
    x--;
  }
  else
    modeline = "Beginning of line";
}

void Editor::moveRight()
{
  if (text.inRange(y, x + 1)) {
      x++;
  }
  else
    modeline = "End of line";
}

bool Editor::handleInput()
{
  noecho();
  cbreak();
  wmove(textWindow, y, x);
  int input = wgetch(textWindow);

  switch(mode) {
  case('n'):
    switch(input) {
    case('q'):
      return false;
    case('i'):
      mode = 'i';
      return true;
    case('j'):
      moveDown();
      return true;
    case('h'):
      moveLeft();
      return true;
    case('k'):
      moveUp();
      return true;
    case('l'):
      moveRight();
      return true;
    default:
      return true;
    }
  case('i'):
    switch(input) {
    case(27): //Escape
      mode = 'n';
      return true;
    case(127): //Backspace
    case(KEY_BACKSPACE):
      moveLeft();
      text.deleteCharacter(y, x);
      return true;
    default:
      text.insertText(y, x, string(1, input));
      moveRight();
    }
  }
  return true;
}
