#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

#define pb push_back
const int MAXN = 2 * 1e5 + 10;

int n, m, k[MAXN], sum = 0;
vector<int> discount[MAXN];

int lastDis[MAXN * 3];
bool check(int d){
	fill(lastDis, lastDis + d + 1, 0);
	for(int i = 1; i <=n; i++){
		if(discount[i].size()==0)continue;
		int l = 0, r = discount[i].size(), m;
		while(r-l > 1){
			m = (l+r)/2;
			if(discount[i][m] <= d)l = m;
			else r = m;
		}
		if(discount[i][l] <= d) lastDis[discount[i][l]] += k[i];
	}
	
	int money = 0, left = sum;
	for(int i = 1; i <= d; i++){
		money++;
		int take = min(lastDis[i], money);
		money -= take;
		left -= take;
		if(!left) return true;
	}
	if(money >= 2 * left) return true;
	return false;
}

int main(){
	cin>>n>>m;
	for(int i = 1; i <= n; i++){
		cin>>k[i];
		sum += k[i];
	}
	int ti, di;
	for(int i = 0; i < m; i++){
		cin>>di>>ti;
		discount[ti].pb(di);
	}
	for(int i = 1; i <= n; i++){
		sort(discount[i].begin(), discount[i].end());
	}
	int l = sum - 1, r = 2 * sum, m;
	while(l + 1 < r){
		m = (l + r) / 2;
		if(check(m))r = m;
		else l = m;
	}
	cout << r << endl;
	
	return 0;
}