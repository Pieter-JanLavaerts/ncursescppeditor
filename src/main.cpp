#include <curses.h>

#include "Editor.h"

int main(int argc, char *argv[])
{
  string filename;

  if (argc > 2) {
    printf("Usage: editor (filename)\n");
  }
  else if (argc == 2) {
    filename = argv[1];
  }
  else {
    filename = "Unnamed";
  }

  initscr();

  Editor editor{filename};

  do {
    editor.printText();
    editor.printStatus();
    editor.printModeline();
  } while (editor.handleInput());

  endwin();
  return 0;
}
