#include<iostream>
#include<algorithm>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

int l, w, tmp, ans;
int dp[2][5000];

int main(){OW0
	while(cin >> l >> w and l and w){
		ans = 0;
		for(int j = 0; j < w; j++){
			cin >> tmp;
			dp[0][j] = (tmp==2 ? 0 : 1);
			if(tmp != 2) ans = 1;
		}
		for(int i = 1; i < l; i++){
			cin >> tmp;
			dp[1][0] = (tmp==2 ? 0 : 1);
			for(int j = 1; j < w; j++){
				cin >> tmp;
				dp[1][j] = (tmp==2 ? 0 : 1);
				if(dp[1][j] != 0)
					dp[1][j] = min(dp[0][j-1], min(dp[0][j], dp[1][j-1])) + 1;
				ans = max(dp[1][j], ans);
			}
			for(int k = 0; k < w; k++){
				dp[0][k] = dp[1][k];
			}
		}
		cout << ans * ans << '\n';
	}
	return 0;
}