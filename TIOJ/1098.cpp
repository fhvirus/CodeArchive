#pragma GCC optimize("Ofast")
#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<utility>
#include<queue>
using namespace std;

#define ll long long
#define pii pair<int, int>
#define ff first
#define ss second
#define For(i,n) for(int i=0;i<n;++i)

const int N = 1e5 + 225;
int t, n, a[N];

inline int gcd(int a, int b){
	while(b){
		a %= b;
		swap(a, b);
	}
	return a;
}
int main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int a, b, c;
	while(cin >> a >> b >> c and (a or b or c)){
		if(c % gcd(a, b) != 0){
			cout << "No\n";
			continue;
		}
		int ans = c / max(a, b) * 2 + 1;
		c %= max(a, b);
		vector<vector<int>> vis(a + 1, vector<int>(b + 1, -1));
		vis[0][0] = 0;
		queue<pii> q;
		q.push({0, 0});
		while(!q.empty()){
			pii u = q.front(); q.pop();
			if(u.ff == c or u.ss == c){
				ans += vis[u.ff][u.ss];
				break;
			}

			pii v;
			v = {0, u.ss};
			if(vis[v.ff][v.ss] == -1){
				vis[v.ff][v.ss] = vis[u.ff][u.ss] + 1;
				q.push(v);
			}
			v = {u.ff, 0};
			if(vis[v.ff][v.ss] == -1){
				vis[v.ff][v.ss] = vis[u.ff][u.ss] + 1;
				q.push(v);
			}
			v = {a, u.ss};
			if(vis[v.ff][v.ss] == -1){
				vis[v.ff][v.ss] = vis[u.ff][u.ss] + 1;
				q.push(v);
			}
			v = {u.ff, b};
			if(vis[v.ff][v.ss] == -1){
				vis[v.ff][v.ss] = vis[u.ff][u.ss] + 1;
				q.push(v);
			}

			int eek = min(u.ff, b - u.ss);
			v = {u.ff - eek, u.ss + eek};
			if(vis[v.ff][v.ss] == -1){
				vis[v.ff][v.ss] = vis[u.ff][u.ss] + 1;
				q.push(v);
			}
			eek = min(a - u.ff, u.ss);
			v = {u.ff + eek, u.ss - eek};
			if(vis[v.ff][v.ss] == -1){
				vis[v.ff][v.ss] = vis[u.ff][u.ss] + 1;
				q.push(v);
			}
		}
		cout << ans << '\n';
	}
	return 0;
}
