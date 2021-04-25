// Knapsack DP is harder than FFT.
#include<iostream>
using namespace std;

#define FOO(i,a,b) for(int i=(a);i<=int(b);++i)
#define OOF(i,a,b) for(int i=(a);i>=int(b);--i)

int n, cur[50], ans[50], cnt;
void insert(int u, int p, int cur[]){
	OOF(i,u,p+1) cur[i] = cur[i-1];
	cur[p] = u;
}
void remove(int u, int p, int cur[]){
	FOO(i,p,u-1) cur[i] = cur[i+1];
	cur[u] = 0;
}
void dfs(int u){
	if(u > n){
		++cnt;
		FOO(i,0,u){
			if(cur[i] > ans[i]){
				FOO(j,0,u) ans[j] = cur[j];
				break;
			} else if(cur[i] < ans[i]) break;
		}
		return;
	}
	FOO(i,1,u-1){
		if(u % (cur[i-1] + cur[i]) != 0) continue;
		insert(u, i, cur);
		dfs(u + 1);
		remove(u, i, cur);
	}
}
int32_t main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> n;
	cur[0] = 0, cur[1] = 1, dfs(2);
	cout << cnt << '\n';
	if(cnt != 0) FOO(i,0,n) cout << ans[i] << ' ';
	return 0;
}
