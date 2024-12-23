#include <bits/stdc++.h>
using namespace std;
int n;

bool is_order(vector<int>& L, vector<int>& R, int l, int r) {
  for (int i = 0; i < n; i++) {
    if (l == L[i] && R[i] == r) {
      return 1;
    }
  }
  return 0;
}

//corrcet Order
bool solution1(vector<int>& L, vector<int>& R, vector<int>& updates) {
  int m = updates.size();
  for (int i = 0; i < m - 1; ++i) {
    for (int j = i+1; j < m; ++j) {
      if (!is_order(L, R, updates[i], updates[j])) return 0;
    }
  }
  return 1;
}

//fixed Order
bool solution2(vector<int>& L, vector<int>& R, vector<int>& updates) {
  int m = updates.size();
  for (int i = 0; i < m - 1; ++i) {
    for (int j = i + 1; j < m; ++j) {
      if (!is_order(L, R, updates[i], updates[j])) {
        int temp = updates[i];
        updates[i] = updates[j];
        updates[j] = temp;
      }
    }
  }
  return 1;
}

vector<int> getNums(string s) {
  vector<int> nums;
  string num = "";
  for(int i = 0; i < s.length(); ++i) {
    if (s[i] == '|' || s[i] == ',' || s[i] == ' ')  {
      int x = stoi(num);
      nums.push_back(x);
      num = "";
    }
    if (s[i] != '|' && s[i] != ',' && s[i] != ' ')
      num += s[i];
  }
  int x = stoi(num);
  nums.push_back(x);
  return nums;
}

int main() {
  ifstream f("in.txt");
  // ifstream f("test.txt");

  if (!f.is_open()){
    cerr << "Error opening file";
    return 1;
  }

  int ans1 = 0;
  int ans2 = 0;
  string s;
  vector<int> L;
  vector<int> R;

  // section 1
  while (getline(f,s)) {
    if (s.length() == 0) break;
    vector<int> nums = getNums(s);
    L.push_back(nums[0]);
    R.push_back(nums[1]);
    n++;
  }

  // section 2
  while (getline(f,s)) {
    vector<int> updates = getNums(s);
    if (solution1(L, R, updates)) {
      // cout << "Correct order" << endl;
      int mid = updates.size() / 2;
      ans1 += updates[mid];
    } else {
      // cout << "Incorrect order" << endl;
      solution2(L, R, updates);
      int mid = updates.size() / 2;
      ans2 += updates[mid];
    }
  }

  cout << "S1:" << ans1 << endl;
  cout << "S2:" << ans2 << endl;

  return 0;
}
