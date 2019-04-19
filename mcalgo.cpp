#include <fstream>
#include <iostream>
#include <sstream>
#include "Graph.h"

using namespace std;


int main(int argc, char *argv[]) {
  string filePath = argv[1];  // "maxcut.in";
  return 0;
}

Graph string_parser(string fpath) {
  int vtxnum, edgenum;
  vector<pair<pair<int, int>, int>> we;
  ifstream openFile(fpath.data());

  if (openFile.is_open()) {
    string line;
    int num;
    stringstream ss;
    getline(openFile, line);

    // first line
    ss.str(line);
    ss >> num;
    vtxnum = num;
    ss >> num;
    edgenum = num;
    ss.clear();
    cout << "vtx: " << vtxnum << endl;
    cout << "edge: " << edgenum << endl;

    // other lines
    while(getline(openFile, line)) {
      ss.str(line);
      cout << "ss: " << line << endl;
      while (ss >> num) {
	      cout << "num: " << num << endl;
      }
      ss.clear();
    }
    openFile.close();
  }
}
