#include <bits/stdc++.h>
#define ll long long

using namespace std;
int m, n;

void print(const vector<int>& v, const vector<char>& ops, ll n) {
  for (int i = 0; i < v.size(); ++i) {
    cout << v[i];
    if (i < ops.size()) {
        cout << " " << ops[i] << " ";
    }
  }
  cout << "= " << n << endl;
}

bool part1DFS(ll n, const vector<int>& v, int index, ll curr, vector<char>& ops) {
  if (index == v.size()) {
    // print(v, ops, curr);
    if (curr == n) {
      return true;
    }
    return false;
  }

  // add
  ops.push_back('+');
  if (part1DFS(n, v, index + 1, curr + v[index], ops)) 
    return true;
  ops.pop_back();

  // mult
  ops.push_back('*');
  if (part1DFS(n, v, index + 1, curr * v[index], ops)) 
    return true;
  ops.pop_back();

  return false;
}

bool part2DFS(ll n, const vector<int>& v, int index, ll curr, vector<char>& ops) {
  if (index == v.size()) {
    // print(v, ops, curr);
    if (curr == n) {
      return true;
    }
    return false;
  }

  // add
  ops.push_back('+');
  if (part2DFS(n, v, index + 1, curr + v[index], ops)) 
    return true;
  ops.pop_back();

  // mult
  ops.push_back('*');
  if (part2DFS(n, v, index + 1, curr * v[index], ops)) 
    return true;
  ops.pop_back();

  ops.push_back('|');
  string conca = to_string(curr) + to_string(v[index]); 
  ll num = stoll(conca);
  // cout << "Concat: " << curr << " c " << v[index] << " : " << num << endl;

  if (part2DFS(n, v, index + 1, num, ops)) 
    return true;
  ops.pop_back();

  return false;
}

int main() {
  ifstream f("in.txt");
  // ifstream f("test.txt");

  if (!f.is_open()){
    cerr << "Error opening file";
    return 1;
  }

  string s;
  ll ans1 = 0;
  ll ans2 = 0;
  vector<int> v;
  while (getline(f,s)) {
    // s = n: [] nums
    // cout << s << endl;
    size_t colonPos = s.find(':');
    ll n = stoll(s.substr(0, colonPos));
    vector<int> v;
    stringstream ss(s.substr(colonPos + 1));
    int num;
    while (ss >> num) {
      v.push_back(num);
    }

    vector<char> ops;
    vector<char> ops2;
    // cout << s;
    if (part1DFS(n, v, 1, v[0], ops)) {
      cout << " -> YES(1)" << endl;
      ans1 += n;
    }else if (part2DFS(n, v, 1, v[0], ops2)) {
      cout << s;
      cout << " -> YES(2)" << endl;
      ans2 += n;
    } else {
      cout << s;
      cout << " -> NO" << endl;
    }
  }

  cout << "S1:" << ans1 << endl;
  cout << "S2:" << ans1 + ans2 << endl;

}
