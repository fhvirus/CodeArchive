#include<iostream>
#include<algorithm>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

int main(){OW0
	int n, m, ans = 0;
	bool pass;
	string in;
	cin >> n >> m;
	cin.ignore();
	for(int i = 0; i < n; i++){
		pass = true;
		for(int j = 0; j < m; j++){
			getline(cin, in);
			if(!all_of(in.begin()+1, in.end(), [](char c){
				return c >= 'a' and c <= 'z';})){
				pass = false;
			}
		}
		ans += pass;
	}
	cout << ans;
	return 0;
}