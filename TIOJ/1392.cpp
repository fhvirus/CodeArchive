#include<iostream>
#include<algorithm>
using namespace std;

const int N = 102;
int n, a[N][N];
bool dp[2][N][N];

int main(){
	while(cin >> n){
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= i; ++j)
				cin >> a[i][j];
		for(int i = 0; i <= n + 1; ++i)
			for(int j = 0; j <= i; ++j)
				dp[0][i][j] = false;

		int done = 1, t = a[1][1];
		dp[0][1][1] = true;
		for(; t <= 100 and done < n * (n + 1) / 2; ++t){
			for(int i = 1; i <= n; ++i){
				for(int j = 1; j <= n; ++j){
					if(t < a[i][j]) continue;
					if(dp[0][i][j]) continue;
					dp[1][i][j] = (
						dp[0][i-1][j-1] or
						dp[0][i-1][j] or
						dp[0][i+1][j] or
						dp[0][i+1][j+1]
					);
					if(dp[1][i][j]) ++done;
				}
			}
		}
		cout << t - 1 << '\n';
	}
}