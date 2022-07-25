#include "randoms.h"

using namespace std;

int randomNum(int upperBound) {
  vector<int> v;
  for (int i = 0; i < upperBound; i++) {
    v.push_back(i);
  }
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  default_random_engine rng{seed};
  shuffle(v.begin(), v.end(), rng);
  return v[0];
}
