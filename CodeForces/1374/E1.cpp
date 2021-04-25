#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

#define eek ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
const int MAXN = 2e5;

int n, k;
vector<int> t, a, b;

int main(){eek
	cin >> n >> k;
	bool alice, bob;
	int time;
	for(int i = 0; i < n; ++i){
		cin >> time >> alice >> bob;
		if(alice and bob) t.push_back(time);
		else if(alice) a.push_back(time);
		else if(bob) b.push_back(time);
	}
	sort(a.begin(), a.end());
	sort(b.begin(), b.end());
	for(int i = 0; i < a.size() and i < b.size(); ++i){
		t.push_back(a[i] + b[i]);
	}
	if(t.size() < k){
		cout << -1;
		return 0;
	}
	sort(t.begin(), t.end());
	
	int ans = 0;
	for(int i = 0; i < k; ++i){
		ans += t[i];
	}
	cout << ans;
	return 0;
}