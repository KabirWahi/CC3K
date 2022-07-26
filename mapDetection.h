#ifndef MAPDETECTION_H
#define MAPDETECTION_H
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void bfs(std::vector<std::string> &map, std::vector<std::vector<bool>> &visited, int i, int j, std::vector<std::pair<int, int>> &pos);

std::vector<std::vector<std::pair<int, int>>> mapDetection(std::vector<std::string> &map);

#endif  // MAPDETECTION_H
