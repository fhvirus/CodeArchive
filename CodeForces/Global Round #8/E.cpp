#include<iostream>
#include<vector>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
const int MAXN = 2e5 + 1;

vector<int> adj[MAXN], ans;
bool vis[MAXN];

int main(){OW0
	int T, n, m, a, b;
	cin >> T;
	for(;T;--T){
		cin >> n >> m;
		for(int i = 1; i <= n; ++i){
			adj[i].clear();
			vis[i] = false;
		}
		ans.clear();
		for(;m;--m){
			cin >> a >> b;
			adj[b].push_back(a);
		}
		for(int i = 1; i <= n; ++i){
			for(int u: adj[i]) if(!vis[u])
				for(int v: adj[u])
					if(!vis[v]){
						vis[i] = true;
						ans.push_back(i);
						goto end;
					}
			end: ;
		}
		cout << ans.size() << '\n';
		for(int i: ans) cout << i << ' ';
		cout << '\n';
	}
	return 0;
}