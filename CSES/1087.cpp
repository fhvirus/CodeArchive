// Adapted from https://codeforces.com/blog/entry/82174
#include <bits/stdc++.h>
using namespace std;

int main() {
	string s, o; cin >> s;
	set<char> st;
	for (const char& c: s)
		if (st.insert(c).second and st.size() == 4) {
			o += c;
			st.clear();
		}
	for (const char& c: "ACGT")
		if (!st.count(c)) {
			o += c;
			break;
		}
	cout << o << '\n';
	return 0;
}
