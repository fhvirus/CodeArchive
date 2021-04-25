#include<iostream>
#include<vector>
using namespace std;

const int N = 3e5+1;
int n, q, a[N+1];
int L[N], ans[N], sum;
vector<int> R[N];

int bit[N+1];


int main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> n >> q;
	for(int i = 1; i <= n; ++i)
		cin >> a[i], a[i] = i - a[i];
	for(int x, y, l, r, i = 0;  i < q; ++i){
		cin >> x >> y;
		l = x + 1, r = n - y;
		L[i] = l, R[r].push_back(i);
	}
	for(int r = 1; r <= n; ++r){
		int jizz = a[r];
		if(jizz >= 0){
			int p = 0, v = sum;
			for(int eek = 1 << (31 - __builtin_clz(n)); eek >= 1; eek >>= 1)
				if(p + eek <= r and v - bit[p + eek] >= jizz)
					p += eek, v -= bit[p];

			++sum;
			for(int i = p + 1; i <= n; i += i & -i)
				++bit[i];
		}
		for(int i: R[r]){
			ans[i] = sum;
			for(int p = L[i]; p > 0; p -= p & -p)
				ans[i] -= bit[p];
		}
	}
	for(int i = 0; i < q; ++i)
		cout << ans[i] << '\n';
}