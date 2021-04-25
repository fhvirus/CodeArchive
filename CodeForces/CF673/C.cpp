#include<iostream>
#include<algorithm>
#include<vector>
#include<stack>
using namespace std;

const int N = 3e5 + 10;
int t, n, k, a[N], last[N], mx[N];

int main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> t;
	for(; t; --t){
		cin >> n;
		for(int i = 0; i <= n; ++i) last[i] = 0, mx[i] = 0;
		for(int i = 1; i <= n; ++i){
			cin >> a[i];
			mx[a[i]] = max(mx[a[i]], i - last[a[i]]);
			last[a[i]] = i;
		}
		for(int i = 0; i <= n; ++i)
			mx[i] = max(mx[i], n + 1 - last[i]);
		vector<int> s;
		for(int i = n; i > 0; --i){
			if(last[i] == 0) continue;
			while(!s.empty() and mx[s.back()] >= mx[i] and s.back() > i) s.pop_back();
			s.push_back(i);
		}
		// for(int i: s){
		// 	cout << i << ' ' << mx[i] << '\n';
		// }
		int p = 0, i = 1;
		while(i < mx[s[p]]) cout << "-1 ", ++i;
		for(; i <= n; ++i){
			if(p != s.size() - 1 and mx[s[p + 1]] == i) ++p;
			cout << s[p] << ' ';
		}
		cout << '\n';
	}
}