#include "mapDetection.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
|-----------------------------------------------------------------------------|
|                                                                             |
| |--------------------------|        |-----------------------|               |
| |..........................|        |.......................|               |
| |..........................+########+.......................|-------|       |
| |..........................|   #    |...............................|--|    |
| |..........................|   #    |..................................|--| |
| |----------+---------------|   #    |----+----------------|...............| |
|            #                 #############                |...............| |
|            #                 #     |-----+------|         |...............| |
|            #                 #     |............|         |...............| |
|            ###################     |............|   ######+...............| |
|            #                 #     |............|   #     |...............| |
|            #                 #     |-----+------|   #     |--------+------| |
|  |---------+-----------|     #           #          #              #        |
|  |.....................|     #           #          #         |----+------| |
|  |.....................|     ########################         |...........| |
|  |.....................|     #           #                    |...........| |
|  |.....................|     #    |------+--------------------|...........| |
|  |.....................|     #    |.......................................| |
|  |.....................+##########+.......................................| |
|  |.....................|          |.......................................| |
|  |---------------------|          |---------------------------------------| |
|                                                                             |
|-----------------------------------------------------------------------------|
*/

void bfs(vector<string> &map, vector<vector<bool>> &visited, size_t i, size_t j, vector<pair<int, int>> &pos) {
  if (i < 0 || i >= map.size() || j < 0 || j >= map[0].size()) {
    return;
  }
  if (visited[i][j]) {
    return;
  }
  visited[i][j] = true;
  pos.push_back(make_pair(i, j));
  bfs(map, visited, i + 1, j, pos);
  bfs(map, visited, i - 1, j, pos);
  bfs(map, visited, i, j + 1, pos);
  bfs(map, visited, i, j - 1, pos);
}

vector<vector<pair<int, int>>> mapDetection(vector<string> &map) {
  vector<vector<bool>> visited(map.size(), vector<bool>(map[0].size(), false));
  for (size_t i = 0; i < map.size(); i++) {
    for (size_t j = 0; j < map[0].size(); j++) {
      if (map[i][j] == '|' || map[i][j] == '-' || map[i][j] == '+' || map[i][j] == '#' || map[i][j] == ' ') {
        visited[i][j] = true;
      }
    }
  }
  int numChambers = 0;
  vector<vector<pair<int, int>>> chambers;
  while (true) {
    bool found = false;
    for (size_t i = 0; i < map.size(); i++) {
      for (size_t j = 0; j < map[0].size(); j++) {
        if (!visited[i][j]) {
          chambers.emplace_back();
          found = true;
          bfs(map, visited, i, j, chambers[numChambers]);
          numChambers++;
        }
      }
    }
    if (!found) {
      break;
    }
  }
  return chambers;
}
