#pragma once

#include <string>
#include <vector>

using namespace std;

class Buffer {
public:
  const string *getLine(int row);
  //returns pointer because getline may fail and return a nullptr
  bool insertText(int row, int collumn, string text);
  bool insertLine(int row, string line);
  bool appendLine(string line);
  bool deleteCharacter(int row, int collumn);
  //bool because methods return whether they succeeded or not
  bool inRange(int row, int collumn = 0);

private:
  vector<string> lines;
};
