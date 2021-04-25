#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<iostream>
#include<string>
#include<vector>
using namespace std;

#define eek ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

int main(){
	int t, len;
	string a, b;
	vector<int> ans;
	cin >> t;
	for(; t; --t){
		ans.clear();
		cin >> len >> a >> b;
		for(int i = 0; i < len-1; ++i){
			if(a[i] != a[i+1]) ans.push_back(i+1);
		}
		if(b[len-1] != a[len-1]) ans.push_back(len);
		for(int i = len - 2; i >= 0; --i){
			if(b[i] != b[i+1]) ans.push_back(i+1);
		}
		cout << ans.size() << ' ';
		for(int i: ans) cout << i << ' ';
		cout << '\n';
	}
	return 0;
}