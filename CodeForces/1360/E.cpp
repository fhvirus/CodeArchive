#include<iostream>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

bool mp[50][50];

int main(){OW0
	int T, n;
	string in;
	bool ans;
	cin >> T;
	for(;T;T--){
		cin >> n;
		cin.ignore();
		for(int i = 0; i < n; i++){
			getline(cin, in);
			for(int j = 0; j < n; j++){
				mp[i][j] = (in[j] == '1');
			}
		}
		ans = true;
		for(int i = 0; i < n-1; i++){
			for(int j = 0; j < n-1; j++){
				if(mp[i][j] and !mp[i+1][j] and !mp[i][j+1]){
					ans = false;
					break;
				}
			}
			if(!ans) break;
		}
		cout << (ans ? "YES\n" : "NO\n");
	}
	return 0;
}