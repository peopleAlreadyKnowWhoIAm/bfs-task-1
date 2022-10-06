#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "mgraph.hpp"

using namespace std;

int main(int argc, char const *argv[]) {
  mGraph m;
  string buf;
  do {
    getline(cin, buf);
    if (buf.empty()) {
      break;
    }
    istringstream iss_buf(buf.c_str());
    int from, to;
    iss_buf >> from;
    iss_buf >> to;
    m.insert(Edge{.from = from, .to = to});

  } while (true);
  cout << m.present_cycle() << endl;

  return 0;
}
