#include<iostream>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
const int MAXN = 2e5+1;

int cur;
int dsu[MAXN], num[MAXN], map[MAXN];
long long sum[MAXN];

void init(int n){
	static int i;
	for(i = 0; i <= n; i++){
		dsu[i] = i;
		num[i] = 1;
		map[i] = i;
		sum[i] = i;
	}
}

int Find(int a){
	return dsu[a] == a ? a : dsu[a] = Find(dsu[a]);
}

void Union(int a, int b){
	if(a == b) return;
	sum[a] += sum[b];
	num[a] += num[b];
	sum[b] = 0;
	num[b] = 0;
	dsu[b] = dsu[a];
}

int main(){OW0
	int n, m, cmd, p, q;
	while(cin >> n >> m){
		init(n+m);
		for(int i = 0; i <= n; i++)
			sum[i] = i;
		cur = n;
		while(m--){
			cin >> cmd >> p;
			if(cmd == 1){
				cin >> q;
				Union(Find(map[p]), Find(map[q]));
			} else if(cmd == 2){
				cin >> q;
				int x = Find(map[p]), y = Find(map[q]);
				if(x != y){
					sum[x] -= p, num[x]--;
					map[p] = ++cur;
					sum[map[p]] = p;
					num[map[p]] = 1;
					Union(Find(map[p]), Find(map[q]));
				}
			} else {
				cout << num[Find(map[p])] <<' '<< sum[Find(map[p])] <<'\n';
			}
		}
	}
	return 0;
}