#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int INF = 1e9;

int dir[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class  Solution {
private:
  int n;
  int m;
  int sx;
  int sy;
  int ex;
  int ey;
  vector<vector<char>> g;
  set<pair<int, int>> p2;

public:
  ll p1;

  void init(vector<vector<char>> grid) {
    p1 = 100000000000;
    g = grid;
    n = grid.size();
    m = grid[0].size();
    findS();
    cout << "Start: " << sx << ", " << sy << endl;
  }

  void findS() {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (g[i][j] == 'S') {
          sx = i;
          sy = j;
        }
        if (g[i][j] == 'E') {
          ex = i;
          ey = j;
        }
      }
    }
  }

  void printGrid() {
    for (int i = 0; i < n; ++i)  {
      for (int j = 0; j < n; ++j) 
        cout << g[i][j];
      cout << endl;
    }
    cout << endl;
  }

  void part1() {
    int ans = 0;

    priority_queue<tuple<int, int, int, int>, vector<tuple<int, int, int, int>>, greater<>> pq;

    vector<vector<vector<int>>> dist(n, vector<vector<int>>(m, vector<int>(4, INF)));

    // east
    pq.push({0, sx, sy, 1}); 
    dist[sx][sy][1] = 0;

    while (!pq.empty()) {
        auto [curr, x, y, prev] = pq.top();
        pq.pop();

        if (g[x][y] == 'E') {
          ans = curr;
          break;
        }

        for (int i = 0; i < 4; ++i) {
          int nx = x + dir[i][0], ny = y + dir[i][1];

          if (nx < 0 || nx >= n || ny < 0 || ny >= m || g[nx][ny] == '#') 
            continue;

          int nc = curr + 1;
          if (prev != i) 
            nc += 1000;

          if (nc < dist[nx][ny][i]) {
            dist[nx][ny][i] = nc;
            pq.push({nc, nx, ny, i});
          }
        }
    }

    p1 = ans;
    cout << "P1: " << ans << endl;
  }

void part2() {
  // dijkstra (path)
  map<pair<pair<int, int>, int>, int> mins;

  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      for (int d = 0; d < 4; ++d)
        mins[{{i, j}, d}] = INF;

  using State = tuple<int, int, int, int, vector<pair<int, int>>>;
  priority_queue<State, vector<State>, greater<>> pq;

  pq.push({0, sx, sy, 1, {{sx, sy}}});

  vector<vector<pair<int, int>>> paths;

  // int best = INF;

  while (!pq.empty()) {
    auto [score, x, y, d, path] = pq.top();
    pq.pop();

    // score > best
    if (score > p1)
        continue;

    if (x == ex && y == ey) {
      // best = score;
      paths.push_back(path);
      continue;
    }

    if (mins[{{x, y}, d}] < score)
      continue;

    mins[{{x, y}, d}] = score;

    for (int i = 0; i < 4; ++i) {
      int nx = x + dir[i][0];
      int ny = y + dir[i][1];

      if (nx < 0 || ny < 0 || nx >= n || ny >= m || g[nx][ny] == '#')
        continue;

      if (find(path.begin(), path.end(), make_pair(nx, ny)) != path.end())
        continue;

      int cost = (i == d) ? 1 : 1001;

      vector<pair<int, int>> np = path;
      np.push_back({nx, ny});
      pq.push({score + cost, nx, ny, i, np});
    }
  }

  set<pair<int, int>> seats;
  for (const auto& path : paths) {
    seats.insert(path.begin(), path.end());
    // for (auto& p : path) {
    //   g[p.first][p.second] = 'O';
    // }
  }
  // printGrid();

  cout << "P2: " << seats.size() << endl;
  }

};


int main(int argc, char* argv[]) {

  string infile = "in.txt";
  if (argc > 1) {
    infile = argv[1];
    infile += ".txt";
  }

  ifstream f(infile);

  if (!f.is_open()){
    cerr << "Error opening file";
    return 1;
  }

  Solution solution;

  string s;

  vector<vector<char>> g;
  while (getline(f,s)) {
    // cout << s << endl;
    vector<char> l(s.begin(), s.end());
    g.push_back(l);
  }

  solution.init(g);

  solution.part1();
  solution.part2();
}
