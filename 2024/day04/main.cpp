
#include <bits/stdc++.h>
using namespace std;

string xmas = "XMAS";
string xmasr = "SAMX";
int m , n;

const char mas[3] = {'M', 'A', 'S'};

//word = MAS or AMX
int find_mas(vector<vector<char>>& grid, int x, int y, int dx, int dy) {
  for (int j = 0; j < 3; j++) {
    x += dx;
    y += dy;
    if (x < 0 || x >= m || y < 0 || y >=  n || grid[x][y] != mas[j]) {
      return false;
    }
  }
  return true;
}

int solution1 (vector<vector<char>> grid) {
  int count = 0;

  int directions[8][2] = {{1, 0}, {1, 1},  {0, 1},  {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      if (grid[i][j] == 'X') {
        for (const auto& dir : directions) {
            count += find_mas(grid, i, j, dir[0], dir[1]);
        }
      }
    }
  }

  return count;
}

bool find_ms_in_d(const vector<vector<char>>& grid, int x, int y, int d) {
    int x1 = x - 1, y1 = (d == 1) ? y - 1 : y + 1; // d == 1: Right diagonal; d == 0: Left diagonal
    int x2 = x + 1, y2 = (d == 1) ? y + 1 : y - 1;

    if (x1 < 0 || y1 < 0 || x2 >= grid.size() || y2 >= grid[0].size()) {
        return 0;
    }

    return (grid[x1][y1] == 'S' && grid[x2][y2] == 'M') ||
           (grid[x1][y1] == 'M' && grid[x2][y2] == 'S');
}

int solution2(vector<vector<char>>& grid) {
    int count = 0;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 'A') {
                bool right = find_ms_in_d(grid, i, j, 1);
                bool left = find_ms_in_d(grid, i, j, -1);
                count += (right && left);
            }
        }
    }

    return count;
}

int main() {
  ifstream f("in.txt");
  // ifstream f("test.txt");

  if (!f.is_open()){
    cerr << "Error opening file";
    return 1;
  }

  string s;
  vector<vector<char>> grid;
  while (getline(f,s)) {
    vector<char> l;
    for (char& c: s) {
      l.push_back(c);
    }
    grid.push_back(l);
  }

  m = grid.size(), n = grid[0].size();
  cout << "S1: " << solution1(grid) << endl; 
  cout << "S2: " << solution2(grid) << endl; 
}
