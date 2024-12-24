#include <bits/stdc++.h>
using namespace std;
int m, n;

int dir[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

void part2(vector<vector<char>>& mp) {
  int m = mp.size(), n = mp[0].size();
  int x = -1, y = -1;

  // find guard initial
  for (int i = 0; i < m && x == -1; ++i) {
      for (int j = 0; j < n; ++j) {
          if (mp[i][j] == '^') {
              x = i, y = j;
              break;
          }
      }
  }

  auto encodeState = [&](int x, int y, int d) {
    return x * n * 4 + y * 4 + d;
  };

  int ans = 0;

  // iterate over all positions
  for (int ox = 0; ox < m; ++ox) {
      for (int oy = 0; oy < n; ++oy) {
        if (mp[ox][oy] == '#' || mp[ox][oy] == '^') 
          continue;

        mp[ox][oy] = '#';
        // set<tuple<int, int, int>> seen;
        unordered_set<int> seen;

        int cd = 0;
        int gx = x, gy = y;

        while (0 <= gx && gx < m && 0 <= gy && gy < n) {
          // seen.insert({gx, gy, cd});
          //
          // Already visited state
          int state = encodeState(gx, gy, cd);
          if (seen.count(state)) break;
          seen.insert(state);

          while (true) {
            int nx = gx + dir[cd][0], ny = gy + dir[cd][1];
            if (0 <= nx && nx < m && 0 <= ny && ny < n && mp[nx][ny] == '#') {
              // Rotate 
              cd = (cd + 1) % 4; 
            } else {
              gx = nx, gy = ny;
              break;
            }
          }
        }

      // if (seen.find({gx, gy, cd}) != seen.end())
      if (seen.count(encodeState(gx, gy, cd)))
        ans += 1;

      // Reset
      mp[ox][oy] = '+'; 
      }
    }

    cout << "S2: " << ans << endl;
}

void part1(vector<vector<char>>& mp) {
  int gx, gy;
  for (int i = 0; i < m; ++i) // find guard
    for (int j = 0; j < m; ++j)
      if (mp[i][j] == '^') {
        gx = i, gy = j;
        break;
      } 

  set<pair<int, int>> seen;

  int cd = 0;
  while (0 <= gx && gx < m && 0 <= gy && gy < n) {
    seen.insert(make_pair(gx, gy));
    while (1) {
      int nx = gx + dir[cd][0], ny = gy + dir[cd][1];
      if (0 <= nx && nx < m && 0 <= ny && ny < n && mp[nx][ny] == '#')
        cd = (cd + 1) % 4;
      else {
        gx = nx, gy = ny;
        break;
      }
    }
  }
  cout << "S1: " << seen.size() << endl;
}

int main() {
  ifstream f("in.txt");
  // ifstream f("test.txt");

  if (!f.is_open()){
    cerr << "Error opening file";
    return 1;
  }

  string s;
  vector<vector<char>> mp;
  while (getline(f,s)) {
    vector<char> l(s.begin(), s.end());
    mp.push_back(l);
  }

  m = mp.size(), n = mp[0].size();

  cout << "ROWS: " << m << endl;
  cout << "COLS: " << n << endl;

  part1(mp);
  part2(mp);
}
