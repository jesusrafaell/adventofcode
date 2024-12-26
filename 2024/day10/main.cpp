#include <bits/stdc++.h>
#define long long ll
using namespace std;
int n, m;

vector<pair<int, int>> dir = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int part1 (vector<vector<int>>& g) {
  int ans = 0;

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      set<pair<int, int>> seen; 
      function<int(int, int)> dfs = [&](int x,int y) {
        if (seen.count({x, y}))
          return 0;
        seen.insert({x, y});
        if (g[x][y] == 9) 
          return 1;

        int res = 0;
        for (auto [dx, dy] : dir) {
          int nx = x + dx, ny = y + dy;
          if (0 <= nx && nx < n && 0 <= ny && ny < m) 
            if (g[nx][ny] == 1 + g[x][y]) 
              res += dfs(nx, ny);
        }
        return res;
      };
      // cout << i << " , " << j << " -> " << g[i][j]  << endl;
      if (g[i][j] == 0)
        ans += dfs(i, j);
    }
  }

  return ans;
}

int part2 (vector<vector<int>>& g) {
  int ans = 0;

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      function<int(int, int)> dfs = [&](int x,int y) {
        if (g[x][y] == 9) 
          return 1;

        int res = 0;
        for (auto [dx, dy] : dir) {
          int nx = x + dx, ny = y + dy;
          if (0 <= nx && nx < n && 0 <= ny && ny < m) 
            if (g[nx][ny] == 1 + g[x][y]) 
              res += dfs(nx, ny);
        }
        return res;
      };
      // cout << i << " , " << j << " -> " << g[i][j]  << endl;
      if (g[i][j] == 0)
        ans += dfs(i, j);
    }
  }

  return ans;
}


int main() {
  ifstream f("in.txt");
  // ifstream f("test.txt");

  if (!f.is_open()){
    cerr << "Error opening file";
    return 1;
  }

  string s;
  vector<vector<int>> grid;
  while (getline(f,s)) {
    vector<int> l;
    for (char& c: s) {
      l.push_back(c - '0');
    }
    grid.push_back(l);
  }

  n = grid.size(), m = grid[0].size();
  cout << "N: " << n << ", M: " << m << endl;

  cout << "S1: " << part1(grid) << endl; 
  cout << "S2: " << part2(grid) << endl; 
}
