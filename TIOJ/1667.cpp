#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

vector<int> S, tmp;

long long merge(int l, int r){
	if(r - l <= 1) return 0;
	int m = (r + l)/2;
	long long ans;
	ans = merge(l, m) + merge(m, r);

	int lptr = l, rptr = m, ptr = l;
	long long rcnt = 0;
	while(lptr < m or rptr < r){
		if(lptr < m and (rptr == r or S[lptr] <= S[rptr])){
			tmp[ptr++] = S[lptr++];
			ans += rcnt;
		} else {
			tmp[ptr++] = S[rptr++];
			rcnt++;
		}
	}
	for(int i = l; i < r; i++)
		S[i] = tmp[i];
	return ans;
}

int main(){OW0
	int n, T = 1;
	while(cin >> n and n){
		S.resize(n);
		tmp.resize(n);
		for(int i = 0; i < n; i++){
			cin >> S[i];
			tmp[i] = S[i];
		}
		sort(tmp.begin(), tmp.end());
		tmp.resize(unique(tmp.begin(), tmp.end()) - tmp.begin());
		for(int i = 0; i < n; i++){
			S[i] = lower_bound(tmp.begin(), tmp.end(), S[i]) - tmp.begin();
		}
	
		cout << merge(0, n) << '\n';
	}
	return 0;
}