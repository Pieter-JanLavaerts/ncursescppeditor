#include "Buffer.h"

const string *Buffer::getLine(int row)
{
  if (row >= 0 && row < lines.size()) {
    return &lines[row];
  }

  return nullptr; //If the line is not in range return nullptr
}

bool Buffer::insertText(int row, int collumn, string text)
{
  if (row < lines.size() && collumn < lines[row].length()) {
    lines[row].insert(collumn, text);
    return true;
  }

  return false;
};

bool Buffer::insertLine(int row, string line)
{
  if (row < lines.size()) {
    lines.insert(lines.begin()+row, line);
    return true;
  }
  if (row == lines.size()) {
    lines.push_back(line);
    return true;
  }
  return false;
}

bool Buffer::appendLine(string line)
{
  return insertLine(lines.size(), line);
}

bool Buffer::deleteCharacter(int row, int collumn)
{
  if (row < lines.size() && collumn < lines[row].length()) {
    lines[row].erase(lines[row].begin()+collumn);
    return true;
  }
  return false;
}

bool Buffer::inRange(int row, int collumn)
{
  if (collumn == 0) {
    return getLine(row);
  }
  else {
    return (collumn >= 0 &&
	    getLine(row) &&
	    collumn < getLine(row)->length()-1);
  }
}
