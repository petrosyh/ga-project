#include <fstream>
#include <iostream>
//#include "Graph.h"

using namespace std;


int main(int argc, char *argv[]) {
  string filePath = argv[1];  // "maxcut.in";
  ifstream openFile(filePath.data());

  if (openFile.is_open()) {
    string line;
    while(getline(openFile, line)) {
      cout << line[2] << endl;
      cout << line << endl;
    }
    openFile.close();
  }
  return 0;
}
