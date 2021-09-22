#include<iostream>
using namespace std;

typedef long long ll;
const int kN = 300003;
int N, a[kN];
int lc[kN], rc[kN];
ll pre[kN];

int stk[kN], top;

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> N;
	for(int i = 1; i <= N; ++i) cin >> a[i];

	// catersian tree
	for(int i = 1; i <= N; ++i){
		// [1, top]
		int k = top;
		while(k > 0 and a[stk[k]] > a[i]) --k;
		if(k > 0) rc[stk[k]] = i;
		if(k < top) lc[i] = stk[k+1];
		stk[++k] = i;
		top = k;
	}
	int root = stk[1];

	// prefix sum
	for(int i = 1; i <= N; ++i) pre[i] = pre[i-1] + a[i];
	auto sum = [](int l, int r){ return pre[r] - pre[l-1]; };

	// simulate
	int lb = 1, rb = N, u = root;
	while(lb < rb){
		if(u == lb) lb = u + 1, u = rc[u];
		else if(u == rb) rb = u - 1, u = lc[u];
		else {
			ll lsum = sum(lb, u-1);
			ll rsum = sum(u+1, rb);
			if(rsum >= lsum) lb = u + 1, u = rc[u];
			else rb = u - 1, u = lc[u];
		}
	}
	cout << a[u];
	return 0;
}
