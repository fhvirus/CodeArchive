#include<iostream>
#include<algorithm>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

int w[20000], h[20000], id[20000], lis[20000], t, m;

int main(){OW0
	cin >> t;
	for(;t;--t){
		cin >> m;
		for(int i = 0; i < m; i++){
			cin >> w[i] >> h[i];
			id[i] = i;
		}
		sort(id, id + m, [](int a, int b){
			if(w[a] != w[b]) return w[a] < w[b];
			return h[a] > h[b];
		});
		fill(lis, lis+m, 1e9);
		for(int i = 0; i < m; i++)
			*lower_bound(lis, lis+m, h[id[i]]) = h[id[i]];
		cout << lower_bound(lis, lis+m, 1e9) - lis << '\n';
	}
	return 0;
}