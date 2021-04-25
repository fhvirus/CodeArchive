#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

const int N = 1e5 + 1;
int n, k[N], ans[N];
vector<int> adj[N];

int main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	for(int i = 1; i <= n; ++i)
		cin >> k[i];
	for(int i = 1, a, b; i < n; ++i){
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	centroidDecomp(1, 0);

	for(int i = 1; i <= n; ++i)
		cout << ans[i] << '\n';
	return 0;
}