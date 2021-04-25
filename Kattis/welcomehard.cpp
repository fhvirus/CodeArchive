#include<iostream>
#include<iomanip>
#include<vector>
#include<cmath>
#include<utility>
using namespace std;

#define eek ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

const string target = "welcome to code jam";
int dp[501][20];
void solve(){
	string in;
	getline(cin, in);
	for(int i = 0; i < 501; i++){
		dp[i][0] = 1;
		for(int j = 1; j < 20; j++){
			dp[i][j] = 0;
		}
	}
	for(int i = 0; i < in.size(); i++){
		for(int j = 0; j < 19 and j <= i; j++){
			if(in[i] == target[j]){
				dp[i+1][j+1] = dp[i][j] + dp[i][j+1];
			} else {
				dp[i+1][j+1] = dp[i][j+1];
			}
			dp[i+1][j+1] %= 10000;
		}
	}
	cout << setw(4) << setfill('0') << dp[in.size()][19] << '\n';
}

int main(){eek
	int T, t;
	cin >> T;
	cin.ignore();
	for(t = 1; t <= T; t++){
		cout << "Case #" << t << ": ";
		solve();
	}
	return 0;
}