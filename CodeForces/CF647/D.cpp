#include<iostream>
#include<algorithm>
#include<vector>
#include<utility>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
const int MAXN = 5e5 + 10;

vector<int> e[MAXN];
pair<int, int> node[MAXN];
int t[MAXN];
bool vis[MAXN] = {0};

int main(){OW0
	int n, m, a, b, cnt;
	cin >> n >> m;
	for(;m;--m){
		cin >> a >> b;
		e[a].push_back(b);
		e[b].push_back(a);
	}
	for(int i = 1; i <= n; i++){
		cin >> a;
		t[i] = a;
		node[i] = {a, i};
	}
	sort(node+1, node+1+n);
	for(int i = 1; i <= n; i++){
		a = node[i].second;
		cnt = 0;
		for(auto k: e[a]){
			if(t[k] < t[a]){
				cnt += (vis[t[k]] == false);
				vis[t[k]] = true;
			}
			if(t[k] == t[a]){
				cout << "-1\n";
				return 0;
			}
		}
		if(cnt != t[a]-1){
			cout << "-1\n";
			return 0;
		}
		for(auto k: e[a]){
			vis[t[k]] = false;
		}
	}
	for(int i = 1; i <= n; i++){
		cout << node[i].second << ' ';
	}
	return 0;
}