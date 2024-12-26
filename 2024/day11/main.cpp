#include <bits/stdc++.h>
#define ll long long
using namespace std;


// memo 
map<pair<ll, int>, ll> memo; 

ll solution(ll x, int n) {
  if (n == 0) return 1;

  pair<ll, int> key = {x, n};
  if (memo.find(key) == memo.end()) {
    // cout << x << " " << n << endl;
    ll result = 0;
    if (x == 0) {
      result = solution(1, n-1);
    } else if (to_string(x).length() % 2 == 0) {
      string sx = to_string(x);
      int mid = sx.length() / 2;
      result += solution(stoll(sx.substr(0, mid)), n -1);
      result += solution(stoll(sx.substr(mid)), n -1);
    } else {
      result = solution(2024 * x, n -1);
    }

    memo[key] = result;
  }

  return memo[key];
}

int main() {
  ifstream f("in.txt");
  // ifstream f("test.txt");

  if (!f.is_open()){
    cerr << "Error opening file";
    return 1;
  }

  string s;
  vector<ll> v; 
  getline(f,s);

  string num = "";
  for (char& c: s) {
    if (c == ' ') {
      v.push_back(stoll(num));
      // v.push_back(num);
      num = "";
    } else 
      num += c;
  }

  // v.push_back(num);
  v.push_back(stoll(num));

  int n = v.size();

  cout << "N: " << n << endl;

  int times = 75; 

  ll ans = 0;
  for (ll x : v) {
    ans += solution(x, times);
  }
  cout << ans << endl;
}
