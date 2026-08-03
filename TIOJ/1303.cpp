#include <bits/stdc++.h>
using namespace std;

const string nej = "Invalid.";
const int max_roman = 3999; // MMM CM XC IX

string to_roman(string s) {
  if (s[0] == '+' or s[0] == '-' or s == "0") return nej;

  int val = 0;
  for (char c : s) {
    val = val * 10 + (c - '0');
    if (val > max_roman) return nej;
  }

  string res;
  for (; val >= 1000; val -= 1000) res += 'M';

  if (val >= 900) val -= 900, res += "CM";
  if (val >= 500) val -= 500, res += 'D';
  if (val >= 400) val -= 400, res += "CD";
  for (; val >= 100; val -= 100) res += 'C';

  if (val >= 90) val -= 90, res += "XC";
  if (val >= 50) val -= 50, res += 'L';
  if (val >= 40) val -= 40, res += "XL";
  for (; val >= 10; val -= 10) res += 'X';

  if (val >= 9) val -= 9, res += "IX";
  if (val >= 5) val -= 5, res += 'V';
  if (val >= 4) val -= 4, res += "IV";
  for (; val >= 1; val -= 1) res += 'I';

  return res;
}

map<string, string> mp;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  for (int i = 1; i <= max_roman; ++i) {
    string s = to_string(i);
    mp[to_roman(s)] = s;
  }

  for (string s; getline(cin, s); ) {
    if (isdigit(s[0]) or '-' == s[0] or '+' == s[0]) cout << to_roman(s) << '\n';
    else cout << (mp.count(s) ? mp.at(s) : nej) << '\n';
  }

  return 0;
}
