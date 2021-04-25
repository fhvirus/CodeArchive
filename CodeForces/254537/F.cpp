#include<iostream>
#include<vector>
#include<set>
#include<utility>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define int long long

vector<pair<int, pair<int, int>>> cmd;
set<pair<int, int>> edge;
vector<string> ans;
int dsu[500000];

void init(int N){
	for(int i = 0; i < N; i++)
		dsu[i] = i;
}

int Find(int a){
	if(dsu[a] == a) return a;
	else return dsu[a] = Find(dsu[a]);
}

void Union(int a, int b){
	if(Find(a) != Find(b)){
		dsu[Find(a)] = Find(b);
	}
}

signed main(){OW0
	int N, M, Q;
	cin >> N >> M >> Q;
	int k, a, b;
	init(N);
	for(int i = 0; i < M; i++){
		cin >> a >> b;
		if(a > b) swap(a, b);
		edge.insert({a, b});
	}
	for(int i = 0; i < Q; i++){
		cin >> k >> a >> b;
		if(a > b) swap(a, b);
		if(k == 1) edge.erase({a, b});
		cmd.push_back({k, {a, b}});
	}
	for(auto i: edge) Union(i.first, i.second);
	for(int i = cmd.size()-1; i >= 0; i--){
		auto w = cmd[i].second;
		if(cmd[i].first == 1)
			Union(w.first, w.second);
		else{
			if(Find(w.first) == Find(w.second))
				ans.push_back("Yes\n");
			else ans.push_back("No\n");
		}
	}
	for(int i = ans.size()-1; i >= 0; i--)
		cout << ans[i];
	return 0;
}