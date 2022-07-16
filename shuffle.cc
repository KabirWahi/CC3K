#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <stdexcept>
#include <string>
#include <vector>

int randomNum(int upperBound) {
  std::vector<int> v;
  for (int i = 0; i < upperBound; i++) {
	v.push_back(i);
  }
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine rng{seed};
  std::shuffle(v.begin(), v.end(), rng);
  return v[0];
}

