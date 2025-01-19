#include <bits/stdc++.h>
using namespace std;
typedef long long ll; typedef pair<int, int> pii;
#define ff first
#define ss second
#define AI(x) begin(x),end(x)
#define pb emplace_back
#ifdef OWO
#define debug(args...) LKJ("\033[1;32m[ " + string(#args) + " ]\033[0m", args)
template<class I> void LKJ(I&&x) { cerr << x << endl; }
template<class I, class...T> void LKJ(I&&x, T&&...t) { cerr << x << ", "; LKJ(t...); }
template<class I> void OI(I a, I b) { while (a < b) cerr << *a << " \n"[next(a) == b], ++a; }
#else
#define debug(...) 0
#define OI(...) 0
#endif
 
signed main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
 
	string s; cin >> s;
	int n = s.length();
 
	vector<int> cnt(26, 0);
	for (char &c: s)
		++cnt[c - 'A'];
 
	int odd = 0;
	for (int &i: cnt)
		odd += (i & 1);
 
	if (odd > 1) {
		cout << "NO SOLUTION\n";
		return 0;
	}
 
	for (int i = 0; i < 26; ++i)
		for (int j = 1; j < cnt[i]; j += 2)
			cout << char('A' + i);
 
	for (int i = 0; i < 26; ++i)
		if (cnt[i] & 1) {
			cout << char('A' + i);
			break;
		}
	
	for (int i = 25; i >= 0; --i)
		for (int j = 1; j < cnt[i]; j += 2)
			cout << char('A' + i);
 
	return 0;
}
