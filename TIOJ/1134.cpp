#include<iostream>
#include<algorithm>
using namespace std;

#define justinlaiorz ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

int t, n, m, a[201][201], eek[201], ans;

int main(){
	justinlaiorz
	cin >> t;
	for(; t; --t){
		cin >> n >> m; ans = 0;
		for(int i = 1; i <= n; ++i){
			for(int j = 1; j <= m; ++j){
				int tmp; cin >> tmp;
				a[i][j] = a[i-1][j] + (tmp == 0 ? 1 : -1);
			}
		}
		for(int u = 0; u < n; ++u){
			for(int d = u + 1; d <= n; ++d){
				for(int i = 1; i <= m; ++i)
					eek[i] = eek[i-1] + a[d][i] - a[u][i];
				for(int l = 0; l < m; ++l)
					for(int r = 1; r <= m; ++r)
						if(eek[r] > eek[l]) ans = max(ans, (d - u) * (r - l));
			}
		}
		cout << ans << '\n';
	}
}