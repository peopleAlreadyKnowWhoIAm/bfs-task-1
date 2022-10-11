#include <gtest/gtest.h>

#include <fstream>

#include "mgraph.hpp"

using namespace std;

// TODO: this must be done completed
TEST(mgraph, add_read_value) {
  mGraph m;

  auto fstr = ifstream("add-read-test-cases/input.txt");

  string buf;
  do {
    getline(fstr, buf);
    if (buf.empty()) {
      break;
    }
    istringstream iss_buf(buf.c_str());
    int from, to;
    iss_buf >> from;
    iss_buf >> to;
    m.insert(Edge{.from = from, .to = to});

  } while (true);

  fstr.close();
}

TEST(mgraph, dijkstra_shortest) {
  vector<pair<string,                 // Adress of file
              vector<pair<int, int>>  // From file pairs target -> min weight
              >>
      data{{"../tests/dijkstra-test/input1.txt", {{4, 13}, {2, 9}, {8, -1}, {1, 8}}},
           {"../tests/dijkstra-test/input2.txt", {{11, 18}, {65, 13}, {57, 20}, {72, 17}}}};
  for (auto&& pair_data : data) {
    mGraph m;

    auto fstr = ifstream(pair_data.first);

    if (!fstr.is_open()) {
      throw "File not open";
    }

    string buf;
    int target;
    do {
      getline(fstr, buf);
      if (buf.empty()) {
        break;
      }
      istringstream iss_buf(buf.c_str());
      int from, to, weight;
      iss_buf >> from;
      iss_buf >> to;
      if (!iss_buf.eof()) {
        iss_buf >> weight;
        m.insert(Edge{.from = from, .to = to, .weight = weight});
      } else {
        target = to;
      }
    } while (true);

    for (auto&& pair_data_result : pair_data.second) {
      int weight = -1;
      auto fn = [&](const int current, const unordered_map<int, From>& visited) {
        if (current == pair_data_result.first) {
          weight = visited.find(current)->second.weight;
          return true;
        }
        return false;
      };

      m.dijkstra(fn);

      ASSERT_EQ(weight, pair_data_result.second)
          << "Not equal weight. Is: " << weight << " Must be: " << pair_data_result.second
          << " on node: " << pair_data_result.first << " in file: " << pair_data.first;
    }
    fstr.close();
  }
}

TEST(mgraph, dijkstra_path_to_all) {
  vector<pair<string,   // Adress of file
              string>>  // Adress of result
      data{{"../tests/dijkstra-test/input1.txt", "../tests/dijkstra-test/output1.txt"},
           {"../tests/dijkstra-test/input2.txt", "../tests/dijkstra-test/output2.txt"}};
  for (auto&& pair_data : data) {
    mGraph m;

    auto fstr = ifstream(pair_data.first);

    if (!fstr.is_open()) {
      throw "File not open";
    }

    string buf;
    int target;
    do {
      getline(fstr, buf);
      if (buf.empty()) {
        break;
      }
      istringstream iss_buf(buf.c_str());
      int from, to, weight;
      iss_buf >> from;
      iss_buf >> to;
      if (!iss_buf.eof()) {
        iss_buf >> weight;
        m.insert(Edge{.from = from, .to = to, .weight = weight});
      } else {
        target = to;
      }
    } while (true);

    int weight = -1;
    auto fun = [&](const int current, const unordered_map<int, From>& visited) {
      stringstream out_visited;
      ifstream out_result(pair_data.second);

      if (!out_result.is_open()) {
        throw "Something";
      }

      for (auto&& par : visited) {
        out_visited << par.first << " " << par.second.weight << endl;
      }

      stringstream file_contents;
      file_contents<< out_result.rdbuf();
      out_result.close();

      EXPECT_EQ(file_contents.str(), out_visited.str())<<"Output wrong with file: "<<pair_data.first;



      return true;
    };

    m.dijkstra(fun, true);

    fstr.close();
  }
}
