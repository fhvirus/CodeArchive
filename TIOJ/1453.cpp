#include<iostream>
#include<algorithm>
using namespace std;

const int N = 1000;
int n, a[N], b[N], id[N], ans[N];

int main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> n;
	for(int i = 0; i < n; ++i)
		cin >> a[i] >> b[i], id[i] = i;
	sort(id, id + n, [](int u, int v){ return b[u] < b[v];});
	for(int i = 0; i < n; ++i){
		ans[i] = 1;
		for(int j = 0; j < n; ++j){
			if(b[i] < a[j])
				ans[i] = max(ans[i], ans[j] + 1);
		}
	}
	int eek = 0;
	for(int i = 0; i < n; ++i)
		eek = max(eek, ans[i]);
	cout << eek;
	return 0;
}