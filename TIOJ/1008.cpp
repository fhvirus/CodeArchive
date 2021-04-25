#pragma GCC optimize("Ofast")
#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<unordered_set>
#include<utility>
using namespace std;

typedef vector<int> vi;
typedef pair<int, vi> piv;
#define ff first
#define ss second

int n, m[5], t;

inline int gcd(int a, int b){
	while(b)
		a %= b, a ^= b, b ^= a, a ^= b;
	return a;
}
inline int hsh(vi vec){
	int ans = 0;
	for(int v: vec)
		ans = ans * 50 + v;
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	while(cin >> n){
		for(int i = 0; i < n; ++i)
			cin >> m[i];
		cin >> t;

		bool oao = false;
		for(int i = 0; i < n; ++i)
			if(m[i] >= t) oao = true;
		if(!oao){
			cout << -1 << '\n';
			continue;
		}

		int g = 0;
		for(int i = 0; i < n; ++i)
			g = gcd(g, m[i]);
		if(t % g){
			cout << -1 << '\n';
			continue;
		}

		bool ans = false;

		queue<piv> q;
		unordered_set<int> vis;
		q.push({0, vi(n,0)});
		vis.insert(hsh(vi(n,0)));

		while(!ans and !q.empty()){
			int stp = q.front().ff;
			vi jiz = q.front().ss;
			q.pop();

			// cout << "Step: " << stp << '\n';
			// for(int i = 0; i < n; ++i)
			// 	cout << jiz[i] << ' ';

			for(int i = 0; i < n; ++i)
				if(jiz[i] == t){
					ans = true;
					cout << stp << '\n';
					break;
				}

			// empty one cup
			for(int i = 0; i < n; ++i){
				vi eek = jiz;
				eek[i] = 0;
				if(vis.count(hsh(eek)) == 0)
					vis.insert(hsh(eek)), q.push({stp + 1, eek});
			}

			// fill one cup
			for(int i = 0; i < n; ++i){
				vi eek = jiz;
				eek[i] = m[i];
				if(vis.count(hsh(eek)) == 0)
					vis.insert(hsh(eek)), q.push({stp + 1, eek});
			}

			// pour from i to j
			for(int i = 0; i < n; ++i){
				for(int j = 0; j < n; ++j){
					if(i == j) continue;
					vi eek = jiz;
					// fill up j
					if(m[j] - eek[j] <= eek[i]){
						eek[i] -= m[j] - eek[j];
						eek[j] = m[j];
					}
					// emtpy i
					else {
						eek[j] += eek[i];
						eek[i] = 0;
					}
					if(vis.count(hsh(eek)) == 0)
						vis.insert(hsh(eek)), q.push({stp + 1, eek});
				}
			}
		}
		if(!ans) cout << -1 << '\n';
	}
	return 0;
}