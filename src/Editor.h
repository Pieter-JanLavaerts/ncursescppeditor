#include <string>
#include <ncurses.h>

#include "Buffer.h"

class Editor {
public:
  Editor(string filename);
  Editor();
  
  bool handleInput(); //returns false when application should be quit
  void printText();
  void printStatus();
  void printModeline();

private:
  string fileName;

  Buffer text;
  WINDOW *textWindow;
  int y, x; //cursor in the textwindow
  int firstLine; //What line is at the top of the window

  char mode;
  string status;
  WINDOW *statusWindow;
  string modeline;
  WINDOW *modeLineWindow;

  void moveUp();
  void moveDown();
  void moveLeft();
  void moveRight();
  void saveFile();
};
