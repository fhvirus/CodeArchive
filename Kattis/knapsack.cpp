#include<iostream>
#include<vector>
#include<cstring>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

inline int max(int a, int b){
	return a > b ? a : b;
}

int v[2000], w[2000], dp[2001];
bool p[2000][2001];
int main(){OW0
	int c, n;
	while(cin >> c >> n){
		for(int i = 0; i < n; i++){
			cin >> v[i] >> w[i];
		}

		memset(dp, 0, sizeof(dp));
		memset(p, false, sizeof(p));

		for(int i = 0; i < n; i++){
			for(int j = c; j - w[i] >= 0; j--){
				if(dp[j] < dp[j-w[i]] + v[i]){
					dp[j] = dp[j-w[i]] + v[i];
					p[i][j] = true;
				}
			}
		}

		int cnt = 0;
		vector<int> ans;
		for(int i = n-1, j = c; i >= 0; i--){
			if(p[i][j]){
				cnt++;
				ans.push_back(i);
				j -= w[i];
			}
		}

		cout << cnt << '\n';
		for(auto i = ans.rbegin(); i != ans.rend(); i++){
			cout << *i << ' ';
		}
		cout << '\n';
	}
	return 0;
}