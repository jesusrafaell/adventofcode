#include <bits/stdc++.h>
using namespace std;

bool part1 (vector<int> report) {
    int n = report.size();
    bool inc = 1, dec = 1;

    for (int i = 0; i < n-1; ++i) {
      int d = report[i+1] - report[i];
      if (d > 0) {
        dec = 0;
      } else if (d < 0){
        inc = 0;
      } 
      if (!(1 <= abs(d) && abs(d) <= 3)) {
        return 0;
      }
    }

    return inc || dec;
}

bool part2 (vector<int> report) {
    int n = report.size();
    bool inc = 1, dec = 1;
    bool del = 0, ok = 0;
    int a = 0;

    for (int i = 0; i < n; ++i) {
      vector<int> newReport(n-1);
      int k = 0;
      for (int j = 0; j < n; ++j) {
        if (j == i) continue;
        newReport[k] = report[j];
        ++k;
      }
      if (part1(newReport)) {
        return 1;
      }
    }

    return 0;
}

int main() {
  ifstream f("input.txt");

  if (!f.is_open()){
    cerr << "Error opening file";
    return 1;
  }

  int ans = 0;
  string s;
  while (getline(f,s)) {
    vector<int> report;
    string num = "";
    for(int i = 0; i < s.length(); ++i) {
      if (s[i] == ' ') {
        int x = stoi(num);
        // cout << x << " ";
        report.push_back(x);
        num = "";
      }
      num += s[i];
    }
    // last num
    int x = stoi(num);
    report.push_back(x);

    // part1
    // if (part1(report)) ++ans;
    
    // part2
    if (part1(report)) 
      ++ans;
    else if (part2(report)) ++ans;


    // init code
  }
  cout << ans << endl;
}
