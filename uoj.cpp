/*
_/_/_/_/    _/_/_/_/_/  _/_/_/
_/      _/      _/    _/      _/
_/      _/      _/    _/      _/
_/      _/      _/    _/      _/
_/      _/      _/    _/  _/  _/
_/      _/  _/  _/    _/    _/_/
_/_/_/_/      _/_/     _/_/_/_/_/

_/_/_/_/    _/    _/  _/      _/
_/      _/   _/  _/   _/_/  _/_/
_/      _/    _/_/    _/ _/_/ _/
_/      _/     _/     _/  _/  _/
_/      _/    _/_/    _/      _/
_/      _/   _/  _/   _/      _/
_/_/_/_/    _/    _/  _/      _/

_/_/_/_/_/ _/_/_/_/_/ _/_/_/_/_/
    _/         _/     _/
    _/         _/     _/
    _/         _/     _/_/_/_/
    _/         _/     _/
    _/         _/     _/
    _/     _/_/_/_/_/ _/_/_/_/_/

_/_/_/_/_/ _/_/_/_/_/ _/_/_/_/_/
    _/         _/     _/
    _/         _/     _/
    _/         _/     _/_/_/_/
    _/         _/     _/
    _/         _/     _/
    _/     _/_/_/_/_/ _/_/_/_/_/
*/
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <cctype>

#include <algorithm>
#include <random>
#include <bitset>
#include <queue>
#include <functional>
#include <set>
#include <map>
#include <vector>
#include <chrono>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <limits>
#include <numeric>

#define LOG(FMT...) fprintf(stderr, FMT)

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

template<class T>
istream &operator>>(istream &is, vector<T> &v) {
  for (T &x : v)
    is >> x;
  return is;
}

template<class T>
ostream &operator<<(ostream &os, const vector<T> &v) {
  if (!v.empty()) {
    os << v.front();
    for (int i = 1; i < v.size(); ++i)
      os << ' ' << v[i];
  }
  return os;
}

int main() {
#ifdef ELEGIA
  freopen("test.in", "r", stdin);
  int nol_cl = clock();
#endif
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  map<int, int> score, last;
  map<int, set<int>> dependencies;
  string line, ipre, isuf, opre, osuf;
  int n = 0;
  while (getline(cin, line)) {
    stringstream str;
    str << line;
    string tok;
    str >> tok;
    if (tok.find("score") != -1) {
      int id = atoi(tok.substr(14).c_str());
      str >> score[id];
    } else if (tok.find("dependence") != -1) {
      int id = atoi(tok.substr(19).c_str());
      str >> tok;
      if (isdigit(tok[0])) {
        dependencies[id].emplace(atoi(tok.c_str()));
      }
    } else if (tok.find("end") != -1) {
      int id = atoi(tok.substr(12).c_str());
      str >> last[id];
    } else if (tok == "input_pre") str >> ipre;
    else if (tok == "input_suf") str >> isuf;
    else if (tok == "output_pre") str >> opre;
    else if (tok == "output_suf") str >> osuf;
    else if (tok == "n_subtasks") str >> n;
  }
  last[0] = 0;
  cout << "subtasks:\n";
  for (int i = 1; i <= n; ++i) {
    cout << "  - scoringType: GroupMin\n"
            "    points: " << score[i] << '\n';
    if (!dependencies[i].empty()) {
      cout << "    dependencies:\n";
      for (int j : dependencies[i]) {
        cout << "      - " << j - 1 << '\n';
      }
    }
    cout << "    testcases:\n";
    for (int j = last[i - 1] + 1; j <= last[i]; ++j) {
      cout << "      - inputFile: " << ipre << j << '.' << isuf << '\n' <<
              "        outputFile: " << opre << j << '.' << osuf << '\n';
    }
  }

#ifdef ELEGIA
  LOG("Time: %dms\n", int ((clock()
          -nol_cl) / (double)CLOCKS_PER_SEC * 1000));
#endif
  return 0;
}
