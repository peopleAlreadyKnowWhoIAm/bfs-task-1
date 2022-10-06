#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "mgraph.hpp"

using namespace std;

int main(int argc, char const *argv[]) {
  mGraph m;
  string buf;
  ifstream file("input.txt");
  if (!file.is_open()) {
    throw '1';
  }
  do {
    getline(file, buf);
    if (buf.empty()) {
      break;
    }
    istringstream iss_buf(buf.c_str());
    int from, to;
    iss_buf >> from;
    iss_buf >> to;
    m.insert(Edge{.from = from, .to = to});

  } while (true);
  file.close();
  cout << m.to_string();

  cout << m.present_cycle() << endl;

  file.close();
  return 0;
}
