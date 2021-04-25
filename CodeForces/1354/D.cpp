#include<iostream>
#include<vector>
using namespace std;

#define eek ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

vector<int> a, k;

inline int cnt(int x){
	int ans = 0;
	for(int i: a)
		if(i <= x) ++ans;
	for(int i: k)
		if(i > 0 and i <= x) ++ans;
		else if(i < 0 and -i <= ans) --ans;
	return ans;
}

int main(){eek
	int n, q;
	cin >> n >> q;
	a.resize(n);
	k.resize(q);
	for(int i = 0; i < n; ++i)
		cin >> a[i];
	for(int i = 0; i < q; ++i)
		cin >> k[i];
	
	if(!cnt(8e7)){
		cout << 0;
		return 0;
	}

	int l = 0, r = 1e6 + 1, m;
	while(r - l > 1){
		m = (l + r)/2;
		if(cnt(m) > 0) r = m;
		else l = m;
	}
	cout << r;
	return 0;
}