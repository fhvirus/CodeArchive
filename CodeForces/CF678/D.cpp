#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

#define ll long long
const int N = 1e5 + 1;
int n, p[N];
ll a[N], sz[N], ans, mxl[N];
vector<int> adj[N];

ll dfs(int u){
	sz[u] = a[u];
	if(adj[u].size() == 0) mxl[u] = a[u];
	for(int v: adj[u])
		sz[u] += dfs(v), mxl[u] = max(mxl[u], mxl[v]);
	return sz[u];
}
ll dfs2(int u){
	if(adj[u].size() == 0)
		return a[u];

	sort(adj[u].begin(), adj[u].end(), [](int i, int j){
		return sz[i] < sz[j];
	});
	ll cursum = a[u] + a[adj[u][0]]; int k = 1;
	while(k < adj[u].size() and a[adj[u][k]] < cursum / k + (cursum % k ? 1 : 0))
		cursum += a[adj[u][k]], ++k;

	ll ans = 0;
	for(int i = 0; i < adj[u].size(); ++i){
		if(i < k){
			ll eek = cursum % k, jiz = cursum / k;
			if(i < eek){
				a[adj[u][i]] = jiz + 1;
			} else {
				a[adj[u][i]] = jiz;
			}
		}
		ans = max(ans, dfs2(adj[u][i]));
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> n;
	for(int i = 2; i <= n; ++i){
		cin >> p[i];
		adj[p[i]].push_back(i);
	}
	for(int i = 1; i <= n; ++i)
		cin >> a[i];
	dfs(1);
	cout << dfs2(1);
	return 0;
}